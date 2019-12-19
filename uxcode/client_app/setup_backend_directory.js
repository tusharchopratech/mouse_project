var fs = require('fs');
fs.createReadStream('../../wearablecode/windows/src/main.exe').pipe(fs.createWriteStream('src/extra-resources/main.exe'));
fs.createReadStream('../../wearablecode/windows/src/iir.dll').pipe(fs.createWriteStream('src/extra-resources/iir.dll'));
fs.createReadStream('../../wearablecode/windows/src/cbw32.dll').pipe(fs.createWriteStream('src/extra-resources/cbw32.dll'));
fs.createReadStream('../../wearablecode/windows/src/cbw64.dll').pipe(fs.createWriteStream('src/extra-resources/cbw64.dll'));