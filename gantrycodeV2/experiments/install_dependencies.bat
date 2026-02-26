@echo off
:: Batch file to run the PowerShell installation script
:: This helps bypass PowerShell execution policy issues

echo ========================================
echo  Dependency Installer Launcher
echo ========================================
echo.
echo This will install dependencies for Bottom Camera Display
echo You may be prompted for Administrator privileges
echo.
pause

:: Run PowerShell script with bypass execution policy
PowerShell -NoProfile -ExecutionPolicy Bypass -Command "& '%~dp0install_dependencies.ps1'"

echo.
echo Installation script completed.
echo Check BUILD_INSTRUCTIONS.txt for next steps.
echo.
pause
