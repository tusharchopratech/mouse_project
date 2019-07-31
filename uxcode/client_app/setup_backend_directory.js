var fs = require('fs');
fs.createReadStream('../../wearablecode/windows/src/main.exe').pipe(fs.createWriteStream('src/extra-resources/main.exe'));
fs.createReadStream('../../wearablecode/windows/src/iir.dll').pipe(fs.createWriteStream('src/extra-resources/iir.dll'));