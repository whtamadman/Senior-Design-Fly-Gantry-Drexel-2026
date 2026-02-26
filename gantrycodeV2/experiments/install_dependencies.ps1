# Installation Script for Bottom Camera Display Dependencies
# This script installs Pylon SDK, OpenCV, and checks for Visual Studio
# Run as Administrator: Right-click and select "Run with PowerShell" or "Run as Administrator"

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Dependency Installer for Bottom Camera" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Check if running as Administrator
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
if (-not $isAdmin) {
    Write-Host "WARNING: Not running as Administrator. Some installations may fail." -ForegroundColor Yellow
    Write-Host "Please right-click this script and select 'Run as Administrator'" -ForegroundColor Yellow
    Write-Host ""
}

# Function to check if a program is installed
function Test-ProgramInstalled {
    param([string]$programName)
    $installed = Get-ItemProperty HKLM:\Software\Microsoft\Windows\CurrentVersion\Uninstall\* |
                 Where-Object { $_.DisplayName -like "*$programName*" }
    if (-not $installed) {
        $installed = Get-ItemProperty HKLM:\Software\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall\* |
                     Where-Object { $_.DisplayName -like "*$programName*" }
    }
    return ($null -ne $installed)
}

# Function to install Chocolatey if not present
function Install-Chocolatey {
    if (-not (Get-Command choco -ErrorAction SilentlyContinue)) {
        Write-Host "[1/4] Installing Chocolatey package manager..." -ForegroundColor Yellow
        Set-ExecutionPolicy Bypass -Scope Process -Force
        [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
        try {
            Invoke-Expression ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
            Write-Host "  ✓ Chocolatey installed successfully" -ForegroundColor Green
            # Refresh environment variables
            $env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User")
        } catch {
            Write-Host "  ✗ Failed to install Chocolatey: $_" -ForegroundColor Red
            return $false
        }
    } else {
        Write-Host "[1/4] Chocolatey already installed ✓" -ForegroundColor Green
    }
    return $true
}

# Function to install Visual Studio Build Tools
function Install-VisualStudio {
    Write-Host "[2/4] Checking for Visual Studio / MSVC..." -ForegroundColor Yellow
    
    # Check for Visual Studio installations
    $vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vsWhere) {
        $vsInstall = & $vsWhere -latest -property installationPath
        if ($vsInstall) {
            Write-Host "  ✓ Visual Studio found at: $vsInstall" -ForegroundColor Green
            return $true
        }
    }
    
    Write-Host "  Visual Studio not found. Installing Visual Studio Build Tools..." -ForegroundColor Yellow
    Write-Host "  NOTE: This will take 10-30 minutes and requires ~5GB of space" -ForegroundColor Cyan
    
    try {
        choco install visualstudio2022buildtools -y --params "--add Microsoft.VisualStudio.Workload.VCTools --includeRecommended"
        Write-Host "  ✓ Visual Studio Build Tools installed" -ForegroundColor Green
        return $true
    } catch {
        Write-Host "  ✗ Failed to install Visual Studio Build Tools" -ForegroundColor Red
        Write-Host "  Manual installation: https://visualstudio.microsoft.com/downloads/" -ForegroundColor Yellow
        return $false
    }
}

# Function to install OpenCV
function Install-OpenCV {
    Write-Host "[3/4] Checking for OpenCV..." -ForegroundColor Yellow
    
    # Check if OpenCV is installed
    $opencvPaths = @(
        "C:\opencv",
        "C:\Program Files\opencv",
        "${env:ProgramFiles(x86)}\opencv"
    )
    
    foreach ($path in $opencvPaths) {
        if (Test-Path $path) {
            Write-Host "  ✓ OpenCV found at: $path" -ForegroundColor Green
            $env:OpenCV_DIR = $path
            [System.Environment]::SetEnvironmentVariable("OpenCV_DIR", $path, "User")
            return $true
        }
    }
    
    Write-Host "  OpenCV not found. Installing via Chocolatey..." -ForegroundColor Yellow
    
    try {
        choco install opencv -y
        Write-Host "  ✓ OpenCV installed" -ForegroundColor Green
        
        # Set OpenCV environment variable
        $opencvInstallPath = "C:\tools\opencv\build"
        if (Test-Path $opencvInstallPath) {
            $env:OpenCV_DIR = $opencvInstallPath
            [System.Environment]::SetEnvironmentVariable("OpenCV_DIR", $opencvInstallPath, "User")
            
            # Add OpenCV to PATH
            $opencvBinPath = "$opencvInstallPath\x64\vc16\bin"
            if (Test-Path $opencvBinPath) {
                $currentPath = [System.Environment]::GetEnvironmentVariable("Path", "User")
                if ($currentPath -notlike "*$opencvBinPath*") {
                    [System.Environment]::SetEnvironmentVariable("Path", "$currentPath;$opencvBinPath", "User")
                    $env:Path += ";$opencvBinPath"
                }
            }
        }
        return $true
    } catch {
        Write-Host "  ✗ Failed to install OpenCV via Chocolatey" -ForegroundColor Red
        Write-Host "  Manual installation:" -ForegroundColor Yellow
        Write-Host "    1. Download: https://opencv.org/releases/" -ForegroundColor Yellow
        Write-Host "    2. Extract to C:\opencv" -ForegroundColor Yellow
        Write-Host "    3. Set OpenCV_DIR environment variable" -ForegroundColor Yellow
        return $false
    }
}

# Function to install Pylon SDK
function Install-PylonSDK {
    Write-Host "[4/4] Checking for Basler Pylon SDK..." -ForegroundColor Yellow
    
    # Check if Pylon is installed
    if (Test-ProgramInstalled "pylon") {
        Write-Host "  ✓ Pylon SDK already installed" -ForegroundColor Green
        return $true
    }
    
    # Check common installation paths
    $pylonPaths = @(
        "C:\Program Files\Basler\pylon 7",
        "C:\Program Files\Basler\pylon 6",
        "${env:ProgramFiles(x86)}\Basler\pylon 7",
        "${env:ProgramFiles(x86)}\Basler\pylon 6"
    )
    
    foreach ($path in $pylonPaths) {
        if (Test-Path $path) {
            Write-Host "  ✓ Pylon SDK found at: $path" -ForegroundColor Green
            $env:PYLON_ROOT = $path
            [System.Environment]::SetEnvironmentVariable("PYLON_ROOT", $path, "User")
            return $true
        }
    }
    
    Write-Host "  Pylon SDK not found." -ForegroundColor Yellow
    Write-Host "  Automatic installation not available for Pylon SDK." -ForegroundColor Yellow
    Write-Host ""
    Write-Host "  Manual installation required:" -ForegroundColor Cyan
    Write-Host "    1. Visit: https://www.baslerweb.com/en/downloads/software-downloads/" -ForegroundColor White
    Write-Host "    2. Download 'pylon Camera Software Suite' for Windows" -ForegroundColor White
    Write-Host "    3. Run the installer and follow the prompts" -ForegroundColor White
    Write-Host "    4. Restart this script after installation" -ForegroundColor White
    Write-Host ""
    
    $response = Read-Host "Have you already installed Pylon SDK manually? (y/n)"
    if ($response -eq 'y' -or $response -eq 'Y') {
        $manualPath = Read-Host "Enter the Pylon installation path (e.g., C:\Program Files\Basler\pylon 7)"
        if (Test-Path $manualPath) {
            $env:PYLON_ROOT = $manualPath
            [System.Environment]::SetEnvironmentVariable("PYLON_ROOT", $manualPath, "User")
            Write-Host "  ✓ Pylon SDK path set" -ForegroundColor Green
            return $true
        }
    }
    
    return $false
}

# Function to create CMakeLists.txt
function Create-CMakeFile {
    Write-Host ""
    Write-Host "Creating CMakeLists.txt for building the project..." -ForegroundColor Yellow
    
    $cmakeContent = @"
cmake_minimum_required(VERSION 3.15)
project(BottomCameraDisplay)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(`${OpenCV_INCLUDE_DIRS})

# Find Pylon SDK
set(PYLON_ROOT "`$ENV{PYLON_ROOT}" CACHE PATH "Pylon SDK root directory")
if(NOT PYLON_ROOT)
    if(EXISTS "C:/Program Files/Basler/pylon 7")
        set(PYLON_ROOT "C:/Program Files/Basler/pylon 7")
    elseif(EXISTS "C:/Program Files/Basler/pylon 6")
        set(PYLON_ROOT "C:/Program Files/Basler/pylon 6")
    endif()
endif()

if(PYLON_ROOT)
    include_directories("`${PYLON_ROOT}/include")
    link_directories("`${PYLON_ROOT}/lib/x64")
    message(STATUS "Pylon SDK found at: `${PYLON_ROOT}")
else()
    message(FATAL_ERROR "Pylon SDK not found. Please set PYLON_ROOT environment variable.")
endif()

# Add executable
add_executable(bottom_camera_display bottom_camera_display.cpp)

# Link libraries
target_link_libraries(bottom_camera_display 
    `${OpenCV_LIBS}
    PylonBase_v7_4.lib
    PylonC_v7_3.lib
    PylonUtility_v7_4.lib
    GenApi_MD_VC141_v3_1_Basler_pylon.lib
    GCBase_MD_VC141_v3_1_Basler_pylon.lib
)

# Copy Pylon DLLs to output directory
add_custom_command(TARGET bottom_camera_display POST_BUILD
    COMMAND `${CMAKE_COMMAND} -E copy_directory
    "`${PYLON_ROOT}/Runtime/x64"
    `$<TARGET_FILE_DIR:bottom_camera_display>
)
"@

    $cmakeFile = Join-Path $PSScriptRoot "CMakeLists.txt"
    Set-Content -Path $cmakeFile -Value $cmakeContent
    Write-Host "  ✓ CMakeLists.txt created" -ForegroundColor Green
}

# Function to create build instructions
function Create-BuildInstructions {
    $instructions = @"
========================================
BUILD INSTRUCTIONS
========================================

All dependencies should now be installed. To build the project:

METHOD 1: Using CMake (Recommended)
------------------------------------
1. Install CMake: https://cmake.org/download/
   Or via Chocolatey: choco install cmake -y

2. Open PowerShell in this directory and run:
   mkdir build
   cd build
   cmake ..
   cmake --build . --config Release

3. Run the program:
   .\Release\bottom_camera_display.exe


METHOD 2: Using Visual Studio
------------------------------
1. Open Visual Studio 2022
2. File → New → Project from Existing Code
3. Select "Visual C++" project type
4. Browse to this folder: $PSScriptRoot
5. Add these include directories (Project Properties → C/C++ → General → Additional Include Directories):
   - `$(PYLON_ROOT)\include
   - `$(OpenCV_DIR)\include
   - .

6. Add these library directories (Project Properties → Linker → General → Additional Library Directories):
   - `$(PYLON_ROOT)\lib\x64
   - `$(OpenCV_DIR)\x64\vc16\lib

7. Add these libraries (Project Properties → Linker → Input → Additional Dependencies):
   - PylonBase_v7_4.lib
   - PylonC_v7_3.lib
   - PylonUtility_v7_4.lib
   - GenApi_MD_VC141_v3_1_Basler_pylon.lib
   - GCBase_MD_VC141_v3_1_Basler_pylon.lib
   - opencv_world4XX.lib (replace XX with your version)

8. Build and Run (F5)


TROUBLESHOOTING
---------------
- If OpenCV not found, set OpenCV_DIR environment variable to your OpenCV build folder
- If Pylon not found, set PYLON_ROOT environment variable to your Pylon installation folder
- Make sure Basler camera is connected before running
- You may need to restart your computer for environment variables to take effect

"@

    $instructionsFile = Join-Path $PSScriptRoot "BUILD_INSTRUCTIONS.txt"
    Set-Content -Path $instructionsFile -Value $instructions
    Write-Host ""
    Write-Host "Build instructions saved to: BUILD_INSTRUCTIONS.txt" -ForegroundColor Cyan
}

# Main installation flow
Write-Host "Starting dependency installation..." -ForegroundColor Cyan
Write-Host ""

$results = @{
    "Chocolatey" = $false
    "VisualStudio" = $false
    "OpenCV" = $false
    "Pylon" = $false
}

$results.Chocolatey = Install-Chocolatey
if ($results.Chocolatey) {
    $results.VisualStudio = Install-VisualStudio
    $results.OpenCV = Install-OpenCV
}
$results.Pylon = Install-PylonSDK

# Summary
Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "INSTALLATION SUMMARY" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan

foreach ($key in $results.Keys) {
    $status = if ($results[$key]) { "✓ INSTALLED" } else { "✗ MISSING" }
    $color = if ($results[$key]) { "Green" } else { "Red" }
    Write-Host "${key}: $status" -ForegroundColor $color
}

Write-Host ""

if ($results.Chocolatey -and $results.VisualStudio -and $results.OpenCV -and $results.Pylon) {
    Write-Host "All dependencies installed successfully! ✓" -ForegroundColor Green
    Create-CMakeFile
    Create-BuildInstructions
    Write-Host ""
    Write-Host "Next steps: See BUILD_INSTRUCTIONS.txt" -ForegroundColor Cyan
} else {
    Write-Host "Some dependencies are missing. Please install them manually." -ForegroundColor Yellow
    Create-BuildInstructions
    Write-Host ""
    Write-Host "Please check BUILD_INSTRUCTIONS.txt for manual installation steps." -ForegroundColor Yellow
}

Write-Host ""
Write-Host "Press any key to exit..."
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
