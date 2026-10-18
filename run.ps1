$ErrorActionPreference = "Stop"

$compiler = "C:\msys64\ucrt64\bin\g++.exe"
$output = ".\PixelSurvivor.exe"

Write-Host "=== Building Pixel Survivor ===" -ForegroundColor Cyan

& $compiler `
    -std=c++17 -Wall -Wextra -g `
    -I"C:\msys64\ucrt64\include" `
    .\main.cpp `
    .\Player.cpp `
    .\Enemy.cpp `
    .\Game.cpp `
    .\Bullet.cpp `
    -o $output `
    -L"C:\msys64\ucrt64\lib" `
    -lraylib -lopengl32 -lgdi32 -lwinmm

if ($LASTEXITCODE -ne 0) {
    Write-Host "`nBuild failed!" -ForegroundColor Red
    Read-Host "Press Enter to exit"
    exit 1
}

Write-Host "`n=== Build successful ===" -ForegroundColor Green

$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

Write-Host "=== Starting game ===" -ForegroundColor Cyan

& $output

if ($LASTEXITCODE -ne 0) {
    Write-Host "`nGame exited with an error." -ForegroundColor Red
    Read-Host "Press Enter to exit"
    exit 1
}