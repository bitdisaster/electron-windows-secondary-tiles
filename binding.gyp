{
  "targets": [
    {
      "target_name": "tile_bindings",
      "sources": [],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "./SecondaryTilesLib/SecondaryTilesLib"
      ],
      "conditions": [
        ['OS=="win"', {
            "sources": ["lib/TileOptions.h","lib/tile_bindings.cc", "lib/TileOptions.cc" ],
            "link_settings": {
              "libraries": ["-lSecondaryTilesLib.lib",]
            }
          }
        ]
      ],      
      "configurations": {
          "Debug": {
            "conditions": [
              ['OS=="win" and target_arch=="x64"', {
                "msvs_settings": {
                  "VCLinkerTool": {
                    "AdditionalLibraryDirectories": [
                      "../SecondaryTilesLib/x64/Debug"
                    ],
                  }
                }
              }],
              ['OS=="win" and target_arch=="ia32"', {
                "msvs_settings": {
                  "VCLinkerTool": {
                    "AdditionalLibraryDirectories": [
                      "../SecondaryTilesLib/Debug"
                    ],
                  }
                }
              }]
            ]
          },
          "Release": {
            "conditions": [
              ['OS=="win" and target_arch=="x64"', {
                "msvs_settings": {
                  "VCLinkerTool": {
                    "AdditionalLibraryDirectories": [
                      "../SecondaryTilesLib/x64/Release"
                    ],
                  }
                }
              }],
              ['OS=="win" and target_arch=="ia32"', {
                "msvs_settings": {
                  "VCLinkerTool": {
                    "AdditionalLibraryDirectories": [
                      "../SecondaryTilesLib/Release"
                    ],
                  }
                }
              }
            ]
          ]
        },
      }
    },
    {
      "target_name": "copy_binary",
      "type":"none",
      'dependencies': ['tile_bindings'],
      "conditions": [['OS=="win" and target_arch=="x64"', {
        "copies":
          [
            {
              'destination': './build/Release',
              'files': ['./SecondaryTilesLib/x64/Release/SecondaryTilesLib.dll']
            },
            {
              'destination': './build/Debug',
              'files': ['./SecondaryTilesLib/x64/Release/SecondaryTilesLib.dll']
            }
          ]
        }],
        ['OS=="win" and target_arch=="ia32"', {
        "copies":
          [
            {
              'destination': './build/Release',
              'files': ['./SecondaryTilesLib/Release/SecondaryTilesLib.dll']
            },
            {
              'destination': './build/Debug',
              'files': ['./SecondaryTilesLib/Release/SecondaryTilesLib.dll']
            }
          ]
        }]]
    }
  ]
}