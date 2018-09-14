const spawn = require('child_process').spawn;

if(process.platform == 'win32') {
    spawn('msbuild', [ '.\\SecondaryTilesLib\\SecondaryTilesLib.sln', '/p:Configuration=Release', '/p:Platform=x64' ]);
    spawn('msbuild', [ '.\\SecondaryTilesLib\\SecondaryTilesLib.sln', '/p:Configuration=Release', '/p:Platform=x86' ]);
}
