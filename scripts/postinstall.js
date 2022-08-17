const { spawn } = require("child_process");

const runtime = process.env.npm_config_cmake_node_runtime || "node";
const runtimeVersion =
  process.env.npm_config_cmake_node_runtimeversion || process.version;
const arch = process.env.npm_config_cmake_node_arch || process.arch;

const runner = spawn(
  "npx",
  [
    "cmake-js",
    "compile",
    "-r",
    runtime,
    "-v",
    runtimeVersion.replace("v", ""),
    "-a",
    arch,
  ],
  { stdio: "inherit" }
);

runner.on("close", () => {
  console.log("[nodejs-mmkv] compile close");
});
runner.on("error", (err) => {
  console.log("[nodejs-mmkv] compile error", err);
});
