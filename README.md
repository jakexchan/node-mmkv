# nodejs-mmkv

Base on [Tencent MMKV](https://github.com/Tencent/MMKV) high-performance key-value storage framework. Implement Node.js.

# Dependencies

- Node.js v16.x, NAPI version 8
- cmake
- C++

# Install

```
npm install --save-dev nodejs-mmkv

// or

yarn add nodejs-mmkv -S
```

You can use it on `Electron`. The first step to setup `cmake` compile configuration:

```
npm config set cmake_node_runtime="electron" # eg: node|iojs|nw|electron
npm config set cmake_node_runtimeversion="x.y.z" # eg: 18.3.5
npm config set cmake_node_arch="x64"  # eg: x64|ia32|arm
```

and run command on your project

```bash
yarn install

// or

npm install
```

# Usage

```bash
const MMKVModule = require("nodejs-mmkv");
const path = require("path");

const mmkv = new MMKVModule({
  rootDir: path.join(__dirname, "./mmkv"),
  id: "com.node.mmkv",
});

// and you can create multiple instance
const logMMKV = new MMKVModule({
  rootDir: path.join(__dirname, "./mmkv"),
  id: "com.app.log",
});
```

## API

### constructor(options: MMKVModuleOptions)

MMKVModule constructor, `options` is required.

`options` properties:

- `rootDir`: File saved path.[required]
- `id`: mmap id, `default: mmkv.default`[optional]
- `multiProcess`: Enable multi process, `default: false`[optional]
- `cryptKey`: encryption key[optional]

### setString: (key: string, value: string) => boolean | undefined;

Set a string value to storage.

### getString: (key: string) => string | undefined;

Get a string value from storage.

### setBoolean: (key: string, value: boolean) => boolean | undefined;

Set a boolean value to storage.

### getBoolean: (key: string) => boolean | undefined;

Get a boolean value from storage.

### setNumber: (key: string, value: number) => boolean | undefined;

Set a number value to storage.

### getNumber: (key: string) => number | undefined;

Get a number value from storage.

### containsKey: (key: string) => boolean | undefined;

Check if the given key exists in storage.

### getKeys: () => string[] | undefined;

Get all keys from storage.

### removeKey: (key: string) => void;

Remove given key and value in storage.

### clearMemoryCache: () => void;

Clear memory cache.

### clearAll: () => void;

Clear all keys and values in storage.

# TODO

- Implement more APIs.
- Test case.

# License

This library is licensed under the MIT license.
