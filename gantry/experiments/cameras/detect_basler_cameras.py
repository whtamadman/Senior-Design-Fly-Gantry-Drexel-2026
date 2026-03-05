"""
Basler Camera Detection Script
Detects and lists all connected Basler cameras using pypylon
"""

import sys
import os

def detect_basler_cameras():
    """Detect and display information about connected Basler cameras"""
    
    # Show Python version and path for debugging
    print("=" * 60)
    print("Python Information")
    print("=" * 60)
    print(f"Python version: {sys.version}")
    print(f"Python executable: {sys.executable}")
    print(f"Python path: {os.path.dirname(sys.executable)}")
    print()
    
    try:
        from pypylon import pylon
        print("✓ pypylon is installed and imported successfully!")
        print()
    except ImportError as e:
        print("ERROR: pypylon is not installed in this Python environment!")
        print(f"\nDetails: {str(e)}")
        print(f"\nCurrent Python: {sys.executable}")
        print("\nTo install pypylon for THIS Python, run:")
        print(f'  "{sys.executable}" -m pip install pypylon')
        print("\nOr simply:")
        print("  python -m pip install pypylon")
        print("\nOr with conda:")
        print("  conda install -c conda-forge pypylon")
        print("\n" + "=" * 60)
        return False
    
    print("=" * 60)
    print("Basler Camera Detection")
    print("=" * 60)
    print()
    
    try:
        # Create an instant camera object with the first found camera device
        tlFactory = pylon.TlFactory.GetInstance()
        
        # Get all attached devices
        devices = tlFactory.EnumerateDevices()
        
        if len(devices) == 0:
            print("No Basler cameras detected!")
            print("\nTroubleshooting:")
            print("  1. Check if cameras are connected via USB/GigE")
            print("  2. Verify Pylon SDK is installed")
            print("  3. Check Device Manager for camera devices")
            print("  4. Try reconnecting the cameras")
            return False
        
        print(f"Found {len(devices)} Basler camera(s):\n")
        print("-" * 60)
        
        for i, device in enumerate(devices):
            print(f"\nCamera {i + 1}:")
            print(f"  Model Name:      {device.GetModelName()}")
            print(f"  Serial Number:   {device.GetSerialNumber()}")
            print(f"  User Name:       {device.GetUserDefinedName()}")
            print(f"  Device Class:    {device.GetDeviceClass()}")
            print(f"  Full Name:       {device.GetFullName()}")
            print(f"  Friendly Name:   {device.GetFriendlyName()}")
            
            # Try to get IP address if it's a GigE camera
            try:
                ip_address = device.GetIpAddress()
                print(f"  IP Address:      {ip_address}")
            except:
                pass
            
            # Try to get interface type
            try:
                interface = device.GetDeviceFactory().GetInterfaceID()
                print(f"  Interface:       {interface}")
            except:
                pass
        
        print("\n" + "-" * 60)
        print("\n✓ Camera detection successful!")
        print("\nTo use these cameras:")
        print("  1. Run dual_basler_display.exe for dual camera display")
        print("  2. Use pypylon in your Python scripts")
        print()
        
        return True
        
    except Exception as e:
        print(f"Error during camera detection: {str(e)}")
        print("\nMake sure:")
        print("  - Pylon SDK is properly installed")
        print("  - Cameras are powered on and connected")
        print("  - You have necessary permissions")
        return False


def test_camera_grab():
    """Test grabbing an image from the first camera"""
    
    try:
        from pypylon import pylon
    except ImportError:
        return False
    
    print("\n" + "=" * 60)
    print("Testing Image Grab from First Camera")
    print("=" * 60)
    
    try:
        camera = pylon.InstantCamera(pylon.TlFactory.GetInstance().CreateFirstDevice())
        camera.Open()
        
        print(f"\nOpened: {camera.GetDeviceInfo().GetModelName()}")
        print(f"Serial: {camera.GetDeviceInfo().GetSerialNumber()}")
        
        # Grab a single image
        print("\nGrabbing test image...")
        camera.StartGrabbingMax(1)
        grabResult = camera.RetrieveResult(5000, pylon.TimeoutHandling_ThrowException)
        
        if grabResult.GrabSucceeded():
            print(f"✓ Image grabbed successfully!")
            print(f"  Image size: {grabResult.Width} x {grabResult.Height}")
            print(f"  Pixel type: {grabResult.PixelType}")
        else:
            print("✗ Image grab failed!")
        
        grabResult.Release()
        camera.Close()
        
        return True
        
    except Exception as e:
        print(f"Error during test grab: {str(e)}")
        return False


if __name__ == "__main__":
    print()
    
    # Detect cameras
    success = detect_basler_cameras()
    
    # If cameras were found, optionally test grabbing
    if success:
        response = input("\nDo you want to test grabbing an image? (y/n): ")
        if response.lower() in ['y', 'yes']:
            test_camera_grab()
    
