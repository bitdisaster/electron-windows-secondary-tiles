

export interface TileOptions {
    Square70x70Logo?: string;
    Square150x150Logo?: string;
    Wide310x150Logo?: string;
    Square310x310Logo?: string;
    BackgroundColor?: string;
    ForegroundText?: ForegroundText;
    ShowNameOnSquare150x150Logo?: boolean;
    ShowNameOnWide310x150Logo?: boolean;
    ShowNameOnSquare310x310Logo?: boolean;
    RoamingEnabled? : boolean;
}

export enum ForegroundText {
    Dark = 0,
    Light = 1
}

export enum TileSize {
    Default = 0,
    Square150x150 = 1,
    Wide310x150 = 2,
}

export function RequestCreate (
    hWnd: object, 
    tileId: string, 
    displayName: string, 
    args: string, 
    squareLogo150x150Uri: string, 
    showNameOnSquare150x150Logo: boolean,
    roamingEnabled: boolean): void;

export function RequestCreateWithOptions (
    hWnd: object, 
    tileId: string, 
    displayName: string, 
    args: string, 
    tileSize: TileSize,
    tileOptions: TileOptions): void;

export function RequestUpdate (
    tileId: string, 
    displayName: string, 
    args: string, 
    squareLogo150x150Uri: string, 
    showNameOnSquare150x150Logo: boolean,
    roamingEnabled: boolean): void;

export function RequestUpdateWithOptions (
    tileId: string, 
    displayName: string, 
    args: string, 
    tileSize: TileSize,
    tileOptions: TileOptions): void;

export function RequestDelete ( tileId: string): void;

export function Exists ( tileId: string): boolean;