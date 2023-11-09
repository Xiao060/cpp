# Arch

## net-tools

```bash
ifconfig: ip addr

netstat: ss
```

## /usr/local/lib 添加到动态库

```shell
vim /etc/ld.so.conf.d/local.conf

# 添加下列内容
/usr/local/lib
```

## 设置终端代理

```shell
export http_proxy=http://127.0.0.1:7890
export https_proxy=$http_proxy
```

## Navicat

```shell
rm -rf ~/.config/navicat
rm -rf ~/.config/dconf/user
```
