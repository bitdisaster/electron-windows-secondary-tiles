const mod = require('../lib/index');

const electron = require('electron')
var ipc = require('electron').ipcMain;

const {
    dialog
} = require('electron')

// Module to control application life.
const app = electron.app
// Module to create native browser window.
const BrowserWindow = electron.BrowserWindow

// Keep a global reference of the window object, if you don't, the window will
// be closed automatically when the JavaScript object is garbage collected.
let mainWindow

function createWindow() {
    // Create the browser window.
    mainWindow = new BrowserWindow({
        width: 800,
        height: 600
    })

    // and load the index.html of the app.
    mainWindow.loadURL(`file://${__dirname}/index.html`)

    // Open the DevTools.
    mainWindow.webContents.openDevTools()

    // Emitted when the window is closed.
    mainWindow.on('closed', function () {
        // Dereference the window object, usually you would store windows
        // in an array if your app supports multi windows, this is the time
        // when you should delete the corresponding element.
        mainWindow = null
    })

    mainWindow.on('focus', function () {
        // Dereference the window object, usually you would store windows
        // in an array if your app supports multi windows, this is the time
        // when you should delete the corresponding element.
    })
}


// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.on('ready', createWindow)

// Quit when all windows are closed.
app.on('window-all-closed', function () {
    // On OS X it is common for applications and their menu bar
    // to stay active until the user quits explicitly with Cmd + Q
    if (process.platform !== 'darwin') {
        app.quit()
    }
})

app.on('activate', function () {
    // On OS X it's common to re-create a window in the app when the
    // dock icon is clicked and there are no other windows open.
    if (mainWindow === null) {
        createWindow()
    }
})

// respond to the 'progress' event
ipc.on('pin-tile1', function (event, arg) {
    console.log("pin request received")

    let hwnd = mainWindow.getNativeWindowHandle();
    mod.RequestCreate(hwnd, 'tile-1', 'Tile 1', 'args', 'ms-appx:///assets/SampleAppx.150x150.png', true, false);
});

ipc.on('pin-tile2', function (event, arg) {
    console.log("pin 2 request received")

    var options = {
        Square70x70Logo: "ms-appx:///assets/SampleAppx.70x70.png",
        Square150x150Logo: "ms-appx:///assets/SampleAppx.150x150.png",
        Wide310x150Logo: "ms-appx:///assets/SampleAppx.310x150.png",
        Square310x310Logo: "ms-appx:///assets/SampleAppx.310x310.png",
        BackgroundColor: "#0026FF",
        ForegroundText: 1,
        ShowNameOnSquare150x150Logo: true,
        ShowNameOnWide310x150Logo: true,
        ShowNameOnSquare310x310Logo: true,
        RoamingEnabled: true
    }
    let hwnd = mainWindow.getNativeWindowHandle();
    mod.RequestCreateWithOptions(hwnd, 'tile-2', 'Tile 2 äöü わたし', 'args', 0, options);
});

ipc.on('pin-tile3', function (event, arg) {
    console.log("pin 3 request received")

    var options = {
        Square150x150Logo: "ms-appx:///assets/SampleAppx.150x150.png",
        Wide310x150Logo: "ms-appx:///assets/SampleAppx.310x150.png",
        Square310x310Logo: "ms-appx:///assets/SampleAppx.310x310.png",
        BackgroundColor: "#FF0000",
        ForegroundText: 0,
        ShowNameOnSquare150x150Logo: true,
        ShowNameOnWide310x150Logo: true,
        ShowNameOnSquare310x310Logo: true,
        RoamingEnabled: true
    }
    let hwnd = mainWindow.getNativeWindowHandle();
    mod.RequestCreateWithOptions(hwnd, 'tile-3', 'Tile 3', 'args', 0, options);
});

ipc.on('pin-tile4', function (event, arg) {
    console.log("pin 4 request received")

    var options = {
        Square150x150Logo: "ms-appx:///assets/SampleAppx.150x150.png",
        Wide310x150Logo: "ms-appx:///assets/SampleAppx.310x150.png",
        BackgroundColor: "#007F0E",
        ForegroundText: 0,
        ShowNameOnSquare150x150Logo: true,
        ShowNameOnWide310x150Logo: true,
        ShowNameOnSquare310x310Logo: true,
        RoamingEnabled: true
    }
    let hwnd = mainWindow.getNativeWindowHandle();
    mod.RequestCreateWithOptions(hwnd, 'tile-4', 'Tile 4', 'args', 0, options);

});

ipc.on('pin-tile5', function (event, arg) {
    console.log("pin 5 request received")

    var options = {
        Square70x70Logo: "ms-appx:///assets/SampleAppx.70x70.png",
        Square150x150Logo: "ms-appx:///assets/SampleAppx.150x150.png",
        Wide310x150Logo: "ms-appx:///assets/SampleAppx.310x150.png",
        Square310x310Logo: "ms-appx:///assets/SampleAppx.310x310.png",
        RoamingEnabled: true
    }
    let hwnd = mainWindow.getNativeWindowHandle();
    mod.RequestCreateWithOptions(hwnd, 'tile-5', 'Tile 5', 'args', 2, options);
});

ipc.on('check-tile', function (event, arg) {
    console.log("check tile:" + arg)

    var exists = mod.Exists(arg);

    dialog.showMessageBox({
        message: "tile exist:" + exists
    });
});

ipc.on('delete-tile', function (event, arg) {
    dialog.showMessageBox({
        message: "delete tile:" + arg
    });

    mod.RequestDelete(arg);
});

ipc.on('update-tile5', function (event, arg) {
    console.log("pin 5 update request received")

    var options = {
        Square70x70Logo: "ms-appx:///assets/SampleAppx.70x70.png",
        Square150x150Logo: "ms-appx:///assets/SampleAppx.150x150.png",
        Wide310x150Logo: "ms-appx:///assets/SampleAppx.310x150.png",
        Square310x310Logo: "ms-appx:///assets/SampleAppx.310x310.png",
        BackgroundColor: "#B200FF",
        ShowNameOnSquare150x150Logo: true,
        ShowNameOnWide310x150Logo: true,
        ShowNameOnSquare310x310Logo: true,
        RoamingEnabled: true
    }
    var bla = mod.RequestUpdateWithOptions('tile-5', 'Tile 5 updated', 'args', 2, options);
    dialog.showMessageBox({
        message: bla
    });
});