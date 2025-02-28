# TOTP video code

You're going to have to install OpenSSL with header files.

On Debian and derivatives:

```shell
sudo apt install -y openssl libssl-dev
```

On macOS:

```shell
brew install openssl@3
```

On macOS, if you use the `clangd` LSP, you will also have to add these lines to `.clangd`, so that `clangd` can find the correct include files:

```
CompileFlags:
  Add: [-I/opt/homebrew/opt/openssl@3/include]
```
