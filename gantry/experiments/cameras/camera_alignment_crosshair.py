"""
Camera Alignment Tool with Crosshairs
======================================

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
- '+/-' - Adjust crosshair size
- 'q' - Quit
"""

import numpy as np
import cv2
import os
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
        self.frozen = False
        self.frozen_frames = []
        self.crosshair_size = 40
        self.snapshot_counter = 0
        
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
            
            print(f"\nFound {len(devices)} Basler camera(s):")
            for i, device in enumerate(devices):
                print(f"  Camera {i}: {device.GetFriendlyName()} (S/N: {device.GetSerialNumber()})")
            
            # Connect cameras
            for i in range(self.num_cameras):
                camera = pylon.InstantCamera(tlFactory.CreateDevice(devices[i]))
                camera.Open()
                camera.StartGrabbing(pylon.GrabStrategy_LatestImageOnly)
                self.cameras.append(camera)
                print(f"  ✓ Camera {i} connected")
            
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
            try:
                grab_result = camera.RetrieveResult(5000, pylon.TimeoutHandling_ThrowException)
                
                if grab_result.GrabSucceeded():
                    img = grab_result.Array
                    
                    # Convert to BGR color
                    if len(img.shape) == 2:
                        img = cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)
                    
                    frames.append(img)
                else:
                    frames.append(None)
                
                grab_result.Release()
                
            except Exception as e:
                print(f"Error grabbing from camera {i}: {e}")
                frames.append(None)
        
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
        Draw ruler markings along edges.
        """
        h, w = img.shape[:2]
        
        # Top ruler (every 50 pixels)
        for x in range(0, w, 50):
            tick_len = 20 if x % 100 == 0 else 10
            cv2.line(img, (x, 0), (x, tick_len), color, 1)
            if x % 100 == 0 and x > 0:
                cv2.putText(img, str(x), (x - 15, 30), 
                           cv2.FONT_HERSHEY_SIMPLEX, 0.4, color, 1)
        
        # Left ruler (every 50 pixels)
        for y in range(0, h, 50):
            tick_len = 20 if y % 100 == 0 else 10
            cv2.line(img, (0, y), (tick_len, y), color, 1)
            if y % 100 == 0 and y > 0:
                cv2.putText(img, str(y), (tick_len + 5, y + 5), 
                           cv2.FONT_HERSHEY_SIMPLEX, 0.4, color, 1)
    
    def add_info_overlay(self, img, camera_idx):
        """
        Add information overlay to image.
        """
        h, w = img.shape[:2]
        cx, cy = w // 2, h // 2
        
        # Camera label
        label = ["Bottom", "Side"][camera_idx] if self.num_cameras == 2 else f"Camera {camera_idx}"
        cv2.putText(img, f"{label} Camera", (10, 30), 
                   cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        
        # Resolution
        cv2.putText(img, f"Resolution: {w}x{h}", (10, 60), 
                   cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 1)
        
        # Center coordinates
        cv2.putText(img, f"Center: ({cx}, {cy})", (10, 85), 
                   cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 1)
        
        # Status
        y_offset = h - 100
        if self.frozen:
            cv2.putText(img, "** FROZEN **", (10, y_offset), 
                       cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
            y_offset += 30
        
        # Instructions
        cv2.putText(img, "g=grid r=rulers f=freeze s=save +/-=size q=quit", 
                   (10, h - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 1)
    
    def save_snapshot(self, frames):
        """
        Save current frames as snapshot images.
        """
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        save_dir = os.path.dirname(__file__)
        
        for i, frame in enumerate(frames):
            if frame is not None:
                camera_name = ["bottom", "side"][i] if self.num_cameras == 2 else f"cam{i}"
                filename = f"alignment_snapshot_{camera_name}_{timestamp}.png"
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
        print("CAMERA ALIGNMENT TOOL - CROSSHAIR MODE")
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
            name = ["Bottom Camera", "Side Camera"][i] if self.num_cameras == 2 else f"Camera {i}"
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
                    
                    # Apply overlays
                    if self.show_grid:
                        self.draw_grid(frame)
                    
                    if self.show_rulers:
                        self.draw_rulers(frame)
                    
                    # Draw crosshair (always visible)
                    self.draw_crosshair(frame, color=(0, 255, 0), thickness=2)
                    
                    # Add info overlay
                    self.add_info_overlay(frame, i)
                    
                    # Display
                    cv2.imshow(window_name, frame)
                
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
                
                elif key == ord('f'):
                    self.frozen = not self.frozen
                    status = "FROZEN" if self.frozen else "LIVE"
                    print(f"Frame: {status}")
                
                elif key == ord('s'):
                    if frames:
                        self.save_snapshot(frames)
                
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
