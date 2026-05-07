"""
Baslar Camera Calibration
=========================

Display live camera feeds with center crosshairs for manual alignment.
Use this to position cameras so they both point at the same target point.

Usage:
- Run script with 1 or 2 cameras connected
- Crosshairs show the center of each camera view
- Place a marker at your target point (e.g., where fly will be)
- Adjust camera positions until marker aligns with both crosshairs
- Press keys to toggle overlays and save snapshots

Controls:
- 'g' - Toggle grid overlay
- 'f' - Toggle freeze frame
- 's' - Save snapshot
- 'r' - Toggle rulers
- 'b' - Toggle Bottom camera header
- 'c' - Toggle crosshair
- 'm' - Toggle clean image mode
- '+/-' - Adjust crosshair size
- 'q' - Quit
"""

import numpy as np
import cv2
import os
import tkinter as tk
from tkinter import ttk, messagebox, simpledialog
from pypylon import pylon
from datetime import datetime


class CameraAlignmentCrosshair:
    """
    Live camera alignment tool with crosshairs for manual calibration.
    """
    
    def __init__(self, num_cameras=2):
        """
        Initialize alignment tool.
        
        Parameters:
        -----------
        num_cameras : int
            Number of cameras to use (1 or 2)
        """
        self.num_cameras = num_cameras
        self.cameras = []
        self.show_grid = False
        self.show_rulers = True
        self.show_bottom_header = True
        self.show_crosshair = True
        self.minimal_view = False
        self.frozen = False
        self.frozen_frames = []
        self.crosshair_size = 40
        self.snapshot_counter = 0
        self.selected_device_indices = []
        self.bottom_only_mode = False
        self.camera_labels = ["Bottom", "Side"] if num_cameras == 2 else [f"Camera {i}" for i in range(num_cameras)]

    def select_camera_ports(self, devices):
        """
        Show camera port selection dialog before starting stream.
        Returns True when user clicks Start.
        """
        role_labels = ["Bottom", "Side"] if self.num_cameras == 2 else [f"Camera {i}" for i in range(self.num_cameras)]

        options = []
        for i, device in enumerate(devices):
            options.append(f"Port {i}: {device.GetFriendlyName()} (S/N: {device.GetSerialNumber()})")

        if not options:
            return False

        selected_indices = []

        root = tk.Tk()
        root.title("Baslar Camera Calibration")
        root.resizable(False, False)

        container = ttk.Frame(root, padding=14)
        container.grid(row=0, column=0, sticky="nsew")

        ttk.Label(
            container,
            text="Choose camera ports for each view, then click Start.",
        ).grid(row=0, column=0, columnspan=2, sticky="w", pady=(0, 10))

        var_list = []
        combo_list = []
        for idx, role in enumerate(role_labels):
            ttk.Label(container, text=f"{role} Camera:").grid(row=idx + 1, column=0, sticky="w", padx=(0, 8), pady=4)
            var = tk.StringVar()
            default_idx = min(idx, len(options) - 1)
            var.set(options[default_idx])
            combo = ttk.Combobox(container, textvariable=var, values=options, state="readonly", width=56)
            combo.grid(row=idx + 1, column=1, sticky="ew", pady=4)
            var_list.append(var)
            combo_list.append(combo)

        bottom_only_var = tk.BooleanVar(value=False)
        if self.num_cameras == 2:
            def on_bottom_only_toggle():
                combo_list[1].configure(state="disabled" if bottom_only_var.get() else "readonly")

            ttk.Checkbutton(
                container,
                text="Bottom camera only",
                variable=bottom_only_var,
                command=on_bottom_only_toggle,
            ).grid(row=len(role_labels) + 1, column=0, columnspan=2, sticky="w", pady=(8, 0))

        button_row = len(role_labels) + (2 if self.num_cameras == 2 else 1)
        button_frame = ttk.Frame(container)
        button_frame.grid(row=button_row, column=0, columnspan=2, sticky="e", pady=(12, 0))

        cancelled = {"value": False}

        def on_start():
            indices = []
            use_bottom_only = self.num_cameras == 2 and bottom_only_var.get()
            vars_to_use = [var_list[0]] if use_bottom_only else var_list
            for var in vars_to_use:
                try:
                    indices.append(options.index(var.get()))
                except ValueError:
                    messagebox.showerror("Invalid selection", "Please choose valid camera ports for each role.")
                    return

            if len(indices) != len(set(indices)) and len(indices) > 1:
                messagebox.showerror("Duplicate selection", "Choose different ports for each camera role.")
                return

            selected_indices.extend(indices)
            self.bottom_only_mode = use_bottom_only
            if self.bottom_only_mode:
                self.num_cameras = 1
                self.camera_labels = ["Bottom"]
            else:
                self.camera_labels = role_labels
            root.destroy()

        def on_cancel():
            cancelled["value"] = True
            root.destroy()

        ttk.Button(button_frame, text="Cancel", command=on_cancel).grid(row=0, column=0, padx=(0, 8))
        ttk.Button(button_frame, text="Start", command=on_start).grid(row=0, column=1)

        root.protocol("WM_DELETE_WINDOW", on_cancel)
        root.mainloop()

        if cancelled["value"] or not selected_indices:
            return False

        self.selected_device_indices = selected_indices
        return True
        
    def connect_cameras(self):
        """
        Connect to Basler cameras.
        Returns True if successful.
        """
        try:
            tlFactory = pylon.TlFactory.GetInstance()
            devices = tlFactory.EnumerateDevices()
            
            if len(devices) == 0:
                print("ERROR: No cameras found!")
                return False
            
            if len(devices) < self.num_cameras:
                print(f"WARNING: Found {len(devices)} cameras, but {self.num_cameras} requested.")
                print(f"Using {len(devices)} camera(s).")
                self.num_cameras = len(devices)
                self.camera_labels = [f"Camera {i}" for i in range(self.num_cameras)]
            
            print(f"\nFound {len(devices)} Basler camera(s):")
            for i, device in enumerate(devices):
                print(f"  Camera {i}: {device.GetFriendlyName()} (S/N: {device.GetSerialNumber()})")

            if not self.select_camera_ports(devices):
                print("Camera selection canceled.")
                return False

            selected_indices = self.selected_device_indices or list(range(self.num_cameras))
            
            # Connect cameras
            for i, device_idx in enumerate(selected_indices):
                camera = pylon.InstantCamera(tlFactory.CreateDevice(devices[device_idx]))
                camera.Open()
                camera.StartGrabbing(pylon.GrabStrategy_LatestImageOnly)
                self.cameras.append(camera)
                role_name = self.camera_labels[i] if i < len(self.camera_labels) else f"Camera {i}"
                print(f"  ✓ {role_name} camera connected on port {device_idx}")
            
            return True
            
        except Exception as e:
            print(f"ERROR connecting to cameras: {e}")
            return False
    
    def grab_frames(self):
        """
        Grab frames from all cameras.
        Returns list of frames.
        """
        frames = []
        
        for i, camera in enumerate(self.cameras):
            grab_result = None
            try:
                # Recover if a camera dropped out of grab mode.
                if not camera.IsGrabbing():
                    camera.StartGrabbing(pylon.GrabStrategy_LatestImageOnly)

                grab_result = camera.RetrieveResult(5000, pylon.TimeoutHandling_Return)

                # Guard against null/invalid result pointers before dereferencing.
                if grab_result is None or (hasattr(grab_result, "IsValid") and not grab_result.IsValid()):
                    print(f"Warning: Camera {i} returned an invalid grab result.")
                    frames.append(None)
                    continue
                
                if grab_result.GrabSucceeded():
                    img = grab_result.Array
                    
                    # Convert to BGR color
                    if len(img.shape) == 2:
                        img = cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)
                    
                    frames.append(img)
                else:
                    if hasattr(grab_result, "GetErrorDescription"):
                        print(f"Warning: Camera {i} grab failed: {grab_result.GetErrorDescription()}")
                    frames.append(None)
                
            except Exception as e:
                print(f"Error grabbing from camera {i}: {e}")
                frames.append(None)
            finally:
                if grab_result is not None:
                    try:
                        grab_result.Release()
                    except Exception:
                        # Ignore release failures when pointer is already invalid.
                        pass
        
        return frames
    
    def draw_crosshair(self, img, color=(0, 255, 0), thickness=2):
        """
        Draw crosshair at center of image.
        """
        h, w = img.shape[:2]
        cx, cy = w // 2, h // 2
        size = self.crosshair_size
        
        # Draw crosshair lines
        cv2.line(img, (cx - size, cy), (cx + size, cy), color, thickness)
        cv2.line(img, (cx, cy - size), (cx, cy + size), color, thickness)
        
        # Draw center circle
        cv2.circle(img, (cx, cy), 5, color, -1)
        cv2.circle(img, (cx, cy), size, color, 1)
        
        # Draw corner markers
        corner_size = 10
        # Top-left
        cv2.line(img, (corner_size, 0), (corner_size, corner_size), color, 1)
        cv2.line(img, (0, corner_size), (corner_size, corner_size), color, 1)
        # Top-right
        cv2.line(img, (w - corner_size, 0), (w - corner_size, corner_size), color, 1)
        cv2.line(img, (w, corner_size), (w - corner_size, corner_size), color, 1)
        # Bottom-left
        cv2.line(img, (corner_size, h), (corner_size, h - corner_size), color, 1)
        cv2.line(img, (0, h - corner_size), (corner_size, h - corner_size), color, 1)
        # Bottom-right
        cv2.line(img, (w - corner_size, h), (w - corner_size, h - corner_size), color, 1)
        cv2.line(img, (w, h - corner_size), (w - corner_size, h - corner_size), color, 1)
    
    def draw_grid(self, img, spacing=50, color=(100, 100, 100)):
        """
        Draw grid overlay.
        """
        h, w = img.shape[:2]
        
        # Vertical lines
        for x in range(0, w, spacing):
            thickness = 2 if x == w // 2 else 1
            cv2.line(img, (x, 0), (x, h), color, thickness)
        
        # Horizontal lines
        for y in range(0, h, spacing):
            thickness = 2 if y == h // 2 else 1
            cv2.line(img, (0, y), (w, y), color, thickness)
    
    def draw_rulers(self, img, color=(255, 255, 0)):
        """
        Draw ruler markings along all image edges.
        """
        h, w = img.shape[:2]
        
        # Top and bottom rulers (every 50 pixels)
        for x in range(0, w, 50):
            tick_len = 20 if x % 100 == 0 else 10
            cv2.line(img, (x, 0), (x, tick_len), color, 1)
            cv2.line(img, (x, h - 1), (x, h - 1 - tick_len), color, 1)
            if x % 100 == 0 and x > 0:
                cv2.putText(img, str(x), (x - 15, 30), 
                           cv2.FONT_HERSHEY_SIMPLEX, 0.4, color, 1)
                cv2.putText(img, str(x), (x - 15, h - 10), 
                           cv2.FONT_HERSHEY_SIMPLEX, 0.4, color, 1)
        
        # Left and right rulers (every 50 pixels)
        for y in range(0, h, 50):
            tick_len = 20 if y % 100 == 0 else 10
            cv2.line(img, (0, y), (tick_len, y), color, 1)
            cv2.line(img, (w - 1, y), (w - 1 - tick_len, y), color, 1)
            if y % 100 == 0 and y > 0:
                cv2.putText(img, str(y), (tick_len + 5, y + 5), 
                           cv2.FONT_HERSHEY_SIMPLEX, 0.4, color, 1)
                cv2.putText(img, str(y), (w - 55, y + 5), 
                           cv2.FONT_HERSHEY_SIMPLEX, 0.4, color, 1)
    
    def add_info_overlay(self, img, camera_idx):
        """
        Add information overlay to image.
        """
        h, w = img.shape[:2]
        
        # Camera label
        label = self.camera_labels[camera_idx] if camera_idx < len(self.camera_labels) else f"Camera {camera_idx}"
        is_bottom_camera = label.strip().lower() == "bottom" or (self.num_cameras == 2 and camera_idx == 0)
        if not (is_bottom_camera and not self.show_bottom_header):
            cv2.putText(img, f"{label} Camera", (10, 30), 
                       cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
            
            # Resolution
            cv2.putText(img, f"Resolution: {w}x{h}", (10, 60), 
                       cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 1)
        
        # Status
        y_offset = h - 100
        if self.frozen:
            cv2.putText(img, "** FROZEN **", (10, y_offset), 
                       cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
            y_offset += 30
        
        # Instructions
        cv2.putText(img, "g=grid r=rulers b=bottom-info c=crosshair f=freeze q=quit", 
                   (10, h - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 1)
    
    def prompt_snapshot_coordinates(self):
        """
        Prompt for manual Cx/Cy and Px/Py pixel coordinates via dialog.
        Returns a tuple (cx, cy, px, py) or None if canceled.
        """
        dialog_root = tk.Tk()
        dialog_root.withdraw()
        dialog_root.attributes("-topmost", True)

        try:
            cx = simpledialog.askinteger("Snapshot Coordinates", "Enter Cx:", parent=dialog_root)
            if cx is None:
                print("Snapshot canceled.")
                return None

            cy = simpledialog.askinteger("Snapshot Coordinates", "Enter Cy:", parent=dialog_root)
            if cy is None:
                print("Snapshot canceled.")
                return None

            px = simpledialog.askinteger("Snapshot Coordinates", "Enter Px:", parent=dialog_root)
            if px is None:
                print("Snapshot canceled.")
                return None

            py = simpledialog.askinteger("Snapshot Coordinates", "Enter Py:", parent=dialog_root)
            if py is None:
                print("Snapshot canceled.")
                return None

        except Exception as e:
            print(f"Coordinate input error: {e}")
            return None
        finally:
            dialog_root.destroy()

        return cx, cy, px, py

    def save_snapshot(self, frames, coords):
        """
        Save current frames as snapshot images.
        """
        cx, cy, px, py = coords
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        save_dir = os.path.join(os.path.dirname(__file__), "frames")
        os.makedirs(save_dir, exist_ok=True)
        
        for i, frame in enumerate(frames):
            if frame is not None:
                label = self.camera_labels[i] if i < len(self.camera_labels) else f"cam{i}"
                camera_name = label.lower().replace(" ", "_")
                filename = f"mapping_{camera_name}_Cx{cx}_Cy{cy}&Px{px}_Py{py}_{timestamp}.png"
                filepath = os.path.join(save_dir, filename)
                cv2.imwrite(filepath, frame)
                print(f"  Saved: {filename}")
        
        self.snapshot_counter += 1
        print(f"✓ Snapshot #{self.snapshot_counter} saved")
    
    def run(self):
        """
        Run the alignment tool.
        """
        print("\n" + "=" * 70)
        print("BASLAR CAMERA CALIBRATION")
        print("=" * 70)
        print(f"\nConfigured for {self.num_cameras} camera(s)")
        print("\nSetup Instructions:")
        print("1. Place a visible marker at your target point")
        print("   (e.g., small LED, colored pin, or cross)")
        print("2. Adjust camera positions until marker aligns with crosshairs")
        print("3. Both crosshairs should point at the same physical location")
        print("4. Use 'g' to toggle grid for more alignment reference")
        print("5. Save snapshots with 's' to document alignment")
        print("\nControls:")
        print("  g - Toggle grid overlay")
        print("  r - Toggle rulers")
        print("  b - Toggle Bottom camera header")
        print("  c - Toggle crosshair")
        print("  m - Toggle clean image mode")
        print("  f - Freeze/unfreeze frame")
        print("  s - Save snapshot images")
        print("  + - Increase crosshair size")
        print("  - - Decrease crosshair size")
        print("  q - Quit")
        print()
        
        if not self.connect_cameras():
            print("Failed to connect cameras!")
            return
        
        print("\n✓ Starting live view...\n")
        
        # Create windows
        window_names = []
        for i in range(self.num_cameras):
            label = self.camera_labels[i] if i < len(self.camera_labels) else f"Camera {i}"
            name = f"{label} Camera"
            window_names.append(name)
            cv2.namedWindow(name, cv2.WINDOW_NORMAL)
        
        try:
            while True:
                # Grab frames (or use frozen frames)
                if not self.frozen:
                    frames = self.grab_frames()
                    if all(f is not None for f in frames):
                        self.frozen_frames = [f.copy() for f in frames]
                else:
                    frames = [f.copy() for f in self.frozen_frames]
                
                # Process and display each frame
                for i, (frame, window_name) in enumerate(zip(frames, window_names)):
                    if frame is None:
                        continue

                    # Keep the original frame untouched so snapshot saves are raw images.
                    display_frame = frame.copy()
                    
                    # In clean mode, show only the raw camera image with no overlays.
                    if not self.minimal_view:
                        # Apply overlays
                        if self.show_grid:
                            self.draw_grid(display_frame)
                        
                        if self.show_rulers:
                            self.draw_rulers(display_frame)
                        
                        # Draw crosshair
                        if self.show_crosshair:
                            self.draw_crosshair(display_frame, color=(0, 255, 0), thickness=2)
                        
                        # Add info overlay
                        self.add_info_overlay(display_frame, i)
                    
                    # Display
                    cv2.imshow(window_name, display_frame)
                
                # Handle keyboard input
                key = cv2.waitKey(30) & 0xFF
                
                if key == ord('q'):
                    print("\nExiting...")
                    break
                
                elif key == ord('g'):
                    self.show_grid = not self.show_grid
                    status = "ON" if self.show_grid else "OFF"
                    print(f"Grid overlay: {status}")
                
                elif key == ord('r'):
                    self.show_rulers = not self.show_rulers
                    status = "ON" if self.show_rulers else "OFF"
                    print(f"Rulers: {status}")

                elif key == ord('b'):
                    self.show_bottom_header = not self.show_bottom_header
                    status = "ON" if self.show_bottom_header else "OFF"
                    print(f"Bottom camera header: {status}")

                elif key == ord('c'):
                    self.show_crosshair = not self.show_crosshair
                    status = "ON" if self.show_crosshair else "OFF"
                    print(f"Crosshair: {status}")

                elif key == ord('m'):
                    self.minimal_view = not self.minimal_view
                    status = "ON" if self.minimal_view else "OFF"
                    print(f"Clean image mode: {status}")
                
                elif key == ord('f'):
                    self.frozen = not self.frozen
                    status = "FROZEN" if self.frozen else "LIVE"
                    print(f"Frame: {status}")
                
                elif key == ord('s'):
                    if frames:
                        coords = self.prompt_snapshot_coordinates()
                        if coords is not None:
                            self.save_snapshot(frames, coords)
                
                elif key == ord('+') or key == ord('='):
                    self.crosshair_size = min(self.crosshair_size + 5, 100)
                    print(f"Crosshair size: {self.crosshair_size}")
                
                elif key == ord('-') or key == ord('_'):
                    self.crosshair_size = max(self.crosshair_size - 5, 10)
                    print(f"Crosshair size: {self.crosshair_size}")
        
        finally:
            # Cleanup
            for camera in self.cameras:
                if camera.IsGrabbing():
                    camera.StopGrabbing()
                camera.Close()
            
            cv2.destroyAllWindows()
            print("\nCameras disconnected.")
            
            if self.snapshot_counter > 0:
                print(f"\n✓ Total snapshots saved: {self.snapshot_counter}")
            
            print("\nAlignment complete!")


def main():
    """
    Main entry point.
    """
    import sys
    
    # Check for command line argument
    num_cameras = 2  # Default to dual camera setup
    
    if len(sys.argv) > 1:
        try:
            num_cameras = int(sys.argv[1])
            if num_cameras not in [1, 2]:
                print(f"Invalid number of cameras: {num_cameras}")
                print("Usage: python camera_alignment_crosshair.py [1|2]")
                return
        except ValueError:
            print("Usage: python camera_alignment_crosshair.py [1|2]")
            return
    
    # Create and run alignment tool
    tool = CameraAlignmentCrosshair(num_cameras=num_cameras)
    tool.run()


if __name__ == "__main__":
    main()
