## Local Dev Setup

* Follow http://developer.getpebble.com/sdk/install/mac/

## Running

`pebble build && pebble install --phone=10.0.1.100`

### Building and Deploying with Xcode

Edit the build script for `fake-iOS-target` to use your phone's IP address. Build 
`fake-iOS-target`. Though the build will fail, the pebble app will have been deployed to 
your watch.