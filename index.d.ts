declare interface MMKVModuleOptions {
  /**
   * File saved path [required].
   */
  rootDir: string;
  /**
   * mmap id, default: mmkv.default
   */
  id?: string;
  /**
   * Enable multi process, default: false
   */
  multiProcess?: boolean;
  /**
   * encryption key
   */
  cryptKey?: string;
  /**
   * log level, default: info
   */
  logLevel?: "debug" | "info" | "warning" | "error" | "none";
}

declare class MMKVModule {
  constructor(options: MMKVModuleOptions);

  setString(key: string, value: string): boolean | undefined;
  getString(key: string): string | undefined;
  setBoolean(key: string, value: boolean): boolean | undefined;
  getBoolean(key: string): boolean | undefined;
  setNumber(key: string, value: number): boolean | undefined;
  getNumber(key: string): number | undefined;

  containsKey(key: string): boolean | undefined;
  getKeys(): string[] | undefined;
  removeKey(key: string): void;
  clearMemoryCache(): void;
  clearAll(): void;
}

export { MMKVModule, MMKVModuleOptions };
