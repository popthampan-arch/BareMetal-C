# VS Code Tips and Tricks

## How to "nuke" the whole VS Code installation data

This removes all the settings, extensions, history. It restores VS Code to a "just freshly installed" state.

**macOS:**
```zsh
rm -rf ~/Library/Application\ Support/Code
rm -rf ~/.vscode
```

**Windows (PowerShell):**
```powershell
Remove-Item -Recurse -Force "$env:APPDATA\Code"
Remove-Item -Recurse -Force "$env:USERPROFILE\.vscode"
```

**Windows (CMD):**
```cmd
rmdir /s /q "%APPDATA%\Code"
rmdir /s /q "%USERPROFILE%\.vscode"
```
