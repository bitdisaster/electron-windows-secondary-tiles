const tileBinding = require('bindings')('tile_bindings')

function ToOptionsObject(tileOptions)
{
    const options = new tileBinding.TileOptions();

    options.Square70x70Logo = tileOptions.Square70x70Logo;
    options.Square150x150Logo = tileOptions.Square150x150Logo;
    options.Wide310x150Logo = tileOptions.Wide310x150Logo;
    options.Square310x310Logo = tileOptions.Square310x310Logo;
    options.BackgroundColor = tileOptions.BackgroundColor;
    options.ForegroundText = tileOptions.ForegroundText;
    options.ShowNameOnSquare150x150Logo = tileOptions.ShowNameOnSquare150x150Logo;
    options.ShowNameOnWide310x150Logo = tileOptions.ShowNameOnWide310x150Logo;
    options.ShowNameOnSquare310x310Logo = tileOptions.ShowNameOnSquare310x310Logo;
    options.RoamingEnabled = tileOptions.RoamingEnabled;
    options.InitialBadgeCount = tileOptions.InitialBadgeCount;

    return options;
}

module.exports = {
        /**
    * Creates a Tile
    * @param {Object} hWnd - The native handle to the Apps Window. Use: mainWindow.getNativeWindowHandle();
    * @param {string} tileId - Id of the tile
    * @param {string} displayName - Display name shown on the Tile
    * @param {string} args - Arguments forwarded to the App when Tile is clicked
    * @param {string} squareLogo150x150Uri - A path to the 150x150 icon
    * @param {boolean} showNameOnSquare150x150Logo - Indicates whether the dispaly name is shown on the Tile
    * @param {boolean} roamingEnabled - Indicates whether the Tile should be roamed across devices
    */
    RequestCreate: function (hWnd, tileId, displayName, args, squareLogo150x150Uri, showNameOnSquare150x150Logo, roamingEnabled) {
        return tileBinding.RequestCreate(hWnd, tileId, displayName, args, squareLogo150x150Uri, showNameOnSquare150x150Logo, roamingEnabled);
    },
    /**
    * Creates a Tile
    * @param {Object} hWnd - The native handle to the Apps Window. Use: mainWindow.getNativeWindowHandle();
    * @param {string} tileId - Id of the tile
    * @param {string} displayName - Display name shown on the Tile
    * @param {string} args - Arguments forwarded to the App when Tile is clicked
    * @param {number} tileSize - Desired tile size. 0 - Default, 1 - Square150x150, 2 - Wide310x150
    * @param {Object} tileOptions - An object carrying all possible option for Live Tiles
    */
    RequestCreateWithOptions: function (hWnd, tileId, displayName, args, tileSize, tileOptions) {
        return tileBinding.RequestCreate(hWnd, tileId, displayName, args, tileSize, ToOptionsObject(tileOptions));
    },
    /**
    * Updates an existing Tile
    * @param {Object} hWnd - The native handle to the Apps Window. Use: mainWindow.getNativeWindowHandle();
    * @param {string} tileId - Id of the tile
    * @param {string} displayName - Display name shown on the Tile
    * @param {string} args - Arguments forwarded to the App when Tile is clicked
    * @param {string} squareLogo150x150Uri - A path to the 150x150 icon
    * @param {boolean} showNameOnSquare150x150Logo - Indicates whether the dispaly name is shown on the Tile
    * @param {boolean} roamingEnabled - Indicates whether the Tile should be roamed across devices
    */
    RequestUpdate: function (tileId, displayName, args, squareLogo150x150Uri, showNameOnSquare150x150Logo, roamingEnabled) {
        return tileBinding.RequestUpdate(tileId, displayName, args, squareLogo150x150Uri, showNameOnSquare150x150Logo, roamingEnabled);
    },
    /**
    * Updates an existing Tile
    * @param {Object} hWnd - The native handle to the Apps Window. Use: mainWindow.getNativeWindowHandle();
    * @param {string} tileId - Id of the tile
    * @param {string} displayName - Display name shown on the Tile
    * @param {string} args - Arguments forwarded to the App when Tile is clicked
    * @param {number} tileSize - Desired tile size. 0 - Default, 1 - Square150x150, 2 - Wide310x150
    * @param {Object} tileOptions - An object carrying all possible option for Live Tiles
    */
    RequestUpdateWithOptions: function (tileId, displayName, args, tileSize, tileOptions) {
        return tileBinding.RequestUpdate(tileId, displayName, args, tileSize, ToOptionsObject(tileOptions));
    },
    /**
    * Checks whether a Tile exists.
    * @param {string} tileId - Id of the tile
    */
    Exists: function (tileId) {
        return tileBinding.Exists(tileId);
    },
    /**
     * Deletes a Tile if it exists.
     * @param {string} tileId - Id of the tile
     */
    RequestDelete: function (tileId) {
        return tileBinding.RequestDelete(tileId);
    },
    /**
     * Sends a notification to a Tile if it exists.
     * @param {string} tileId - Id of the tile
     * @param {string} contentXml - Valid UWP notification XML
     */
    Notify: function (tileId, contentXml) {
        return tileBinding.Notify(tileId, contentXml);
    },
    /**
     * Sends a badge notification to a Tile if it exists.
     * @param {string} tileId - Id of the tile
     * @param {string} contentXml - Valid UWP badge XML
     */
    BadgeNotify: function (tileId, badgeXml) {
        return tileBinding.BadgeNotify(tileId, badgeXml);
    },
    /**
     * Clears notification on a Tile if it exists.
     * @param {string} tileId - Id of the tile
     */
    ClearNotification: function (tileId) {
        return tileBinding.ClearNotification(tileId);
    },
    /**
     * Clears notification on a Tile if it exists.
     * @param {string} tileId - Id of the tile
     */
    ClearBadge: function (tileId) {
        return tileBinding.ClearBadge(tileId);
    }
}