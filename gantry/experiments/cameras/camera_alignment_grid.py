"""
Camera Alignment Grid - Visual Reference Tool
==============================================

Displays a reference grid on screen to help visualize camera angle and position.
Shows the camera feed alongside the grid pattern for alignment checking.

Usage:
- Run the script
- Point your camera at the screen displaying the grid
- Adjust camera position/angle while viewing the live feed
- Press 'q' to quit
- Press 'g' to toggle grid style
- Press '+'/'-' to adjust grid size
"""

import numpy as np
import cv2
from pypylon import pylon
import sys


class CameraAlignmentTool:
    """
    Display reference grid and camera feed for alignment visualization.
    """
    
    def __init__(self):
        self.grid_spacing = 50  # pixels between grid lines
        self.grid_style = 'lines'  # 'lines', 'dots', or 'checkerboard'
        self.camera = None
        
    def create_grid_pattern(self, width, height):
        """
        Create a reference grid pattern.
        """
        # Create white background
        grid = np.ones((height, width, 3), dtype=np.uint8) * 255
        
        if self.grid_style == 'lines':
            # Draw vertical lines
            for x in range(0, width, self.grid_spacing):
                color = (0, 0, 0) if x % (self.grid_spacing * 5) == 0 else (200, 200, 200)
                thickness = 2 if x % (self.grid_spacing * 5) == 0 else 1
                cv2.line(grid, (x, 0), (x, height), color, thickness)
            
            # Draw horizontal lines
            for y in range(0, height, self.grid_spacing):
                color = (0, 0, 0) if y % (self.grid_spacing * 5) == 0 else (200, 200, 200)
                thickness = 2 if y % (self.grid_spacing * 5) == 0 else 1
                cv2.line(grid, (0, y), (width, y), color, thickness)
            
            # Add center crosshair
            cv2.line(grid, (width//2 - 30, height//2), (width//2 + 30, height//2), 
                    (255, 0, 0), 2)
            cv2.line(grid, (width//2, height//2 - 30), (width//2, height//2 + 30), 
                    (255, 0, 0), 2)
            
        elif self.grid_style == 'dots':
            # Draw dots at intersections
            for x in range(0, width, self.grid_spacing):
                for y in range(0, height, self.grid_spacing):
                    color = (0, 0, 0) if (x % (self.grid_spacing * 5) == 0 and 
                                         y % (self.grid_spacing * 5) == 0) else (100, 100, 100)
                    radius = 4 if color == (0, 0, 0) else 2
                    cv2.circle(grid, (x, y), radius, color, -1)
            
            # Center marker
            cv2.circle(grid, (width//2, height//2), 8, (255, 0, 0), 2)
            
        elif self.grid_style == 'checkerboard':
            # Create checkerboard pattern
            num_squares_x = width // self.grid_spacing
            num_squares_y = height // self.grid_spacing
            
            for i in range(num_squares_x):
                for j in range(num_squares_y):
                    if (i + j) % 2 == 0:
                        x1 = i * self.grid_spacing
                        y1 = j * self.grid_spacing
                        x2 = x1 + self.grid_spacing
                        y2 = y1 + self.grid_spacing
                        cv2.rectangle(grid, (x1, y1), (x2, y2), (0, 0, 0), -1)
        
        # Add text info
        cv2.putText(grid, f"Grid Size: {self.grid_spacing}px", (10, 30),
                   cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 150, 0), 2)
        cv2.putText(grid, f"Style: {self.grid_style}", (10, 60),
                   cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 150, 0), 2)
        cv2.putText(grid, "Press 'g' to change style, +/- for size, 'q' to quit", 
                   (10, height - 20), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 255), 2)
        
        return grid
    
    def connect_camera(self, camera_index=0):
        """
        Connect to Basler camera.
        """
        try:
            tlFactory = pylon.TlFactory.GetInstance()
            devices = tlFactory.EnumerateDevices()
            
            if len(devices) == 0:
                print("ERROR: No cameras found!")
                return False
            
            print(f"Found {len(devices)} Basler camera(s)")
            print(f"Connecting to camera {camera_index}...")
            
            self.camera = pylon.InstantCamera(tlFactory.CreateDevice(devices[camera_index]))
            self.camera.Open()
            self.camera.StartGrabbing(pylon.GrabStrategy_LatestImageOnly)
            
            print("✓ Camera connected!")
            return True
            
        except Exception as e:
            print(f"ERROR connecting to camera: {e}")
            return False
    
    def grab_camera_frame(self):
        """
        Grab a frame from the camera.
        """
        try:
            grab_result = self.camera.RetrieveResult(5000, pylon.TimeoutHandling_ThrowException)
            
            if grab_result.GrabSucceeded():
                img = grab_result.Array
                
                # Convert to BGR if grayscale
                if len(img.shape) == 2:
                    img = cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)
                
                grab_result.Release()
                return img
            else:
                return None
                
        except Exception as e:
            print(f"Error grabbing frame: {e}")
            return None
    
    def run(self):
        """
        Run the alignment tool.
        """
        print("\n" + "=" * 70)
        print("CAMERA ALIGNMENT GRID TOOL")
        print("=" * 70)
        print("\nControls:")
        print("  'g' - Change grid style (lines/dots/checkerboard)")
        print("  '+' - Increase grid spacing")
        print("  '-' - Decrease grid spacing")
        print("  'q' - Quit")
        print("\nSetup:")
        print("1. This window will display a reference grid")
        print("2. Move this window to a second monitor if available")
        print("3. Point your camera at the grid display")
        print("4. A second window will show the camera's view")
        print("5. Adjust camera position/angle as needed")
        print()
        
        # Connect camera
        if not self.connect_camera():
            print("Failed to connect camera. Showing grid only...")
            camera_connected = False
        else:
            camera_connected = True
        
        # Get screen size for grid
        import tkinter as tk
        root = tk.Tk()
        screen_width = root.winfo_screenwidth()
        screen_height = root.winfo_screenheight()
        root.destroy()
        
        # Use a reasonable size (or fullscreen on secondary monitor)
        grid_width = min(1920, screen_width)
        grid_height = min(1080, screen_height)
        
        print(f"Grid display size: {grid_width}x{grid_height}")
        print("\nStarting...")
        
        cv2.namedWindow('Reference Grid', cv2.WINDOW_NORMAL)
        cv2.resizeWindow('Reference Grid', grid_width, grid_height)
        
        if camera_connected:
            cv2.namedWindow('Camera View', cv2.WINDOW_NORMAL)
        
        try:
            while True:
                # Create and display grid
                grid = self.create_grid_pattern(grid_width, grid_height)
                cv2.imshow('Reference Grid', grid)
                
                # Display camera feed
                if camera_connected:
                    frame = self.grab_camera_frame()
                    if frame is not None:
                        # Add overlay info
                        h, w = frame.shape[:2]
                        cv2.putText(frame, f"Camera View - {w}x{h}", (10, 30),
                                   cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
                        
                        # Add center crosshair
                        cv2.line(frame, (w//2 - 20, h//2), (w//2 + 20, h//2), 
                                (0, 255, 0), 2)
                        cv2.line(frame, (w//2, h//2 - 20), (w//2, h//2 + 20), 
                                (0, 255, 0), 2)
                        
                        cv2.imshow('Camera View', frame)
                
                # Handle keyboard input
                key = cv2.waitKey(30) & 0xFF
                
                if key == ord('q'):
                    print("\nExiting...")
                    break
                
                elif key == ord('g'):
                    # Cycle through grid styles
                    styles = ['lines', 'dots', 'checkerboard']
                    current_idx = styles.index(self.grid_style)
                    self.grid_style = styles[(current_idx + 1) % len(styles)]
                    print(f"Grid style: {self.grid_style}")
                
                elif key == ord('+') or key == ord('='):
                    self.grid_spacing = min(self.grid_spacing + 10, 200)
                    print(f"Grid spacing: {self.grid_spacing}px")
                
                elif key == ord('-') or key == ord('_'):
                    self.grid_spacing = max(self.grid_spacing - 10, 20)
                    print(f"Grid spacing: {self.grid_spacing}px")
        
        finally:
            if camera_connected and self.camera is not None:
                self.camera.StopGrabbing()
                self.camera.Close()
            cv2.destroyAllWindows()
        
        print("Done!")


def main():
    """
    Main entry point.
    """
    tool = CameraAlignmentTool()
    tool.run()


if __name__ == "__main__":
    main()
