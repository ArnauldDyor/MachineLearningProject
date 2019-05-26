const Path = require('path');
const Hapi = require('hapi');
const Inert = require('inert');
const fs = require('fs');
const sharp = require('sharp');

const server = new Hapi.Server({
    port: 3000,
    routes: {
        files: {
            relativeTo: __dirname
        }
    }
});

const provision = async () => {

    await server.register(Inert);
    let indix = 0;
    function sleep(ms){
        return new Promise(resolve=>{
            setTimeout(resolve,ms)
        })
    }
     
    server.route({
        method: 'GET',
        path: '/app/{path*}',
        handler: {
            directory: {
                path: './client/build/',
                listing: false,
                index: true
            }
        }
    });

    server.route({
        method: 'POST',
        path: '/submit',
        config: {

            cors: {
                origin: ['*'],
                additionalHeaders: ['cache-control', 'x-requested-with']
            },

            payload: {
                output: 'stream',
                parse: true,
                allow: 'multipart/form-data'
            },

            handler: async function (request, h) {

                console.log('Receiving image...\n');
                let data = request.payload;
                if (data.file) {
                    let name = data.file.hapi.filename;
                    console.log('\tFilename : ' + name + '\n');
                    let path = __dirname + "/upload/" + indix + '_' + name;
                    indix++;
                    let file = fs.createWriteStream(path);
                    
                    const transformer = sharp()
                    .resize(100, 100)
                    .on('info', function(info){
                        console.log(info);
                        console.log("\n");
                        console.log("Image saved and transformed");
                    });

                    file.on('error', function (err) {
                        console.error(err)
                        return h.response(err).code(500);
                    });

                    data.file.pipe(transformer).pipe(file);
                }
                await sleep(3000);

                if (Math.round(Math.random())) {
                    return h.response('frFlag').code(200);
                }
                else {
                    return h.response('usaFlag').code(200);
                }
            }
        }
    });

    await server.start();

    console.log('Server running at:', server.info.uri);
};

provision();