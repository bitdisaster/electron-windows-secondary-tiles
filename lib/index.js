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

    return options;
}

module.exports = {
    RequestCreate: function (hWnd, tileId, displayName, args, squareLogo150x150Uri, showNameOnSquare150x150Logo, roamingEnabled) {
        return tileBinding.RequestCreate(hWnd, tileId, displayName, args, squareLogo150x150Uri, showNameOnSquare150x150Logo, roamingEnabled);
    },
    RequestCreateWithOptions: function (hWnd, tileId, displayName, args, tileSize, tileOptions) {
        return tileBinding.RequestCreate(hWnd, tileId, displayName, args, tileSize, ToOptionsObject(tileOptions));
    },
    RequestUpdate: function (hWnd, tileId, displayName, args, squareLogo150x150Uri, showNameOnSquare150x150Logo, roamingEnabled) {
        return tileBinding.RequestUpdate(hWnd, tileId, displayName, args, squareLogo150x150Uri, showNameOnSquare150x150Logo, roamingEnabled);
    },
    RequestUpdateWithOptions: function (hWnd, tileId, displayName, args, tileSize, tileOptions) {
        return tileBinding.RequestUpdate(hWnd, tileId, displayName, args, tileSize, ToOptionsObject(tileOptions));
    },
    Exists: function (tileId) {
        return tileBinding.Exists(tileId);
    },
    RequestDelete: function (tileId) {
        return tileBinding.RequestDelete(tileId);
    }
}