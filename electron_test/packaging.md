# rebuild for electron
./node_modules/.bin/electron-rebuild -v 1.7.6

#package electron app
electron-packager ./ electrontiles --out c:/output --electron-version 1.7.6 --overwrite

#package store app
electron-windows-store --input-directory C:\output\electrontiles-win32-x64\  --output-directory C:\output\storeapp --flatten true --package-version 1.0.0.0 --package-name electrontiles --assets C:\output\assets