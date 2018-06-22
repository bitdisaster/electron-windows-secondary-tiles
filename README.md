# electron-windows-secondary-tiles
Pin secondary tiles on Windows 10 from Electron Apps

```
npm install --save electron-windows-secondary-tiles
```

## Pinning a Secondary Tile
Pinning tiles is only availble in the context of UWP Apps and therefor your Electron must be packaged via the Desktop Bridge. A easy way to create a UWP package for an Electron App is via [`electron-windows-store`](https://github.com/felixrieseberg/electron-windows-store).  There are 2 methods available to pin a secondary tile.

First, the most simple variation:
```
RequestCreate(hWnd, tileId, displayName, args, squareLogo150x150Uri, showNameOnSquare150x150Logo, roamingEnabled);
```

* `Object` hWnd - The native handle to the Apps Window. Use: mainWindow.getNativeWindowHandle();
* `string` tileId - Id of the tile
* `string` displayName - Display name shown on the Tile
* `string` args - Arguments forwarded to the App when Tile is clicked
* `string` squareLogo150x150Uri - A path to the 150x150 icon
* `boolean` showNameOnSquare150x150Logo - Indicates whether the dispaly name is shown on the Tile
* `boolean` roamingEnabled - Indicates whether the Tile should be roamed across devices

### Example 1:
```
const {SecondaryTiles} = require('electron-windows-secondary-tiles')

let hwnd = mainWindow.getNativeWindowHandle();
SecondaryTiles.RequestCreate(hwnd, 'tile1', 'Hello Tile 1`, 'myargs', 'ms-appx:///assets/SampleAppx.150x150.png', true, false);
```

The second variation lets you set all possible parameter of a tile via an options object.
```
RequestCreateWithOptions (hWnd, tileId, displayName, args, tileSize, tileOptions)
```

* `Object` hWnd - The native handle to the Apps Window. Use: mainWindow.getNativeWindowHandle();
* `string` tileId - Id of the tile
* `string` displayName - Display name shown on the Tile
* `string` args - Arguments forwarded to the App when Tile is clicked
* `number` tileSize - Desired tile size. 0 - Default, 1 - Square150x150, 2 - Wide310x150
* `Object` tileOptions - An object carrying all possible option for Live Tiles

The option parameter can carry the following parameters:

* `string` Square70x70Logo - The path to icon shown on the small Tile.
* `string` Square150x150Logo - The path to icon shown on the medium Tile.
* `string` Wide310x150Logo - The path to icon shown on the wide Tile.
* `string` Square310x310Logo - The path to icon shown on the large Tile.
* `string` BackgroundColor - The color of Tile. Leave empty to use systems accent color.
* `string` ForegroundText - Indicates whther to use dark or light forground color. 0 - Dark , 1 - Light
* `string` ShowNameOnSquare150x150Logo - Indicates whether the dispaly name is shown on the medium Tile
* `string` ShowNameOnWide310x150Logo - Indicates whether the dispaly name is shown on the wide Tile
* `string` ShowNameOnSquare310x310Logo - Indicates whether the dispaly name is shown on the large Tile
* `string` RoamingEnabled - Indicates whether the Tile should be roamed across devices


### Example 2:
```
const {SecondaryTiles} = require('electron-windows-secondary-tiles')

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
SecondaryTiles.RequestCreateWithOptions(hwnd, 'tile2', 'Hello Tile 2', 'myargs', 0, options);
```

## Updating a Secondary Tile
Updating tiles uses the exact same parameters as creating tiles minus the window handle. Just use the counter part methods `RequestUpdate` and `RequestUpdateWithOptions`;

### Example 3:

```
const {SecondaryTiles} = require('electron-windows-secondary-tiles')

var options = {
    Square70x70Logo: "ms-appx:///assets/SampleAppx.70x70.png",
    Square150x150Logo: "ms-appx:///assets/SampleAppx.150x150.png",
    Wide310x150Logo: "ms-appx:///assets/SampleAppx.310x150.png",
    Square310x310Logo: "ms-appx:///assets/SampleAppx.310x310.png",
    BackgroundColor: "#0026FF",
    ForegroundText: 0,
    ShowNameOnSquare150x150Logo: false,
    ShowNameOnWide310x150Logo: false,
    ShowNameOnSquare310x310Logo: false,
    RoamingEnabled: true
    }

SecondaryTiles.RequestUpdateWithOptions('tile2', 'Hello Tile 2 updated', 'myargs', 0, options);
```

## Deleting Secondary Tile
In order to delete a Tile its Id needs to be known.

### Example 4:
```
const {SecondaryTiles} = require('electron-windows-secondary-tiles')

SecondaryTiles.RequestDelete(`tile1`);
```

## Checking a Secondary Tile
With a given Id the existence of an Tile can be checked.

### Example 5:
```
const {SecondaryTiles} = require('electron-windows-secondary-tiles')

SecondaryTiles.Exists(`tile1`);
```

## Sending notifications to a Secondary tiles
Each Tile can be a receiver of notifications. The notifications can be differently formatted. The content and layout is defined via XML snippets. See the documentation [`here`](https://docs.microsoft.com/en-us/uwp/schemas/tiles/tilesschema/schema-root).

> :warning: BEWARE: Secondary Tile notifications were broken in the Fall Creators Update. Microsoft shipped a fix for RS4. The notification method check for a min version of 10.0.17134.81. On any OS version below that, Notifications will be ignored.

### Example 6:
```
const {SecondaryTiles} = require('electron-windows-secondary-tiles')

SecondaryTiles.Notify(`tile1`, `<tile><visual>
    <binding template = "TileSmall">
        <text hint-style = "caption">Jennifer Parker</text>
    </binding>
    <binding template = "TileMedium">
        <text hint-style = "caption">Jennifer Parker</text>
    </binding>
    <binding template = "TileWide">
        <text hint-style = "caption">Jennifer Parker</text>
    </binding>
    <binding template = "TileLarge">
        <text hint-style = "caption">Jennifer Parker</text>
    </binding></visual></tile>`);
```

License

MIT. Please see LICENSE for details.

