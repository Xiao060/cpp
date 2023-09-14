# Git

## 安装

```shell
// 初始化仓库
git init

// 设置用户名, 邮箱
git config --global user.name "John Doe"
git config --global user.email johndoe@example.com

// 设置编辑器
git config --global core.editor neovim
```



## 基础命令

<img src="https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202308261126199.png" style="zoom: 80%;" />

```shell
// 查看当前仓库状态
// untracked: *.o / 可执行程序
// tracked: *.h / *.c / Makefile
git status

// 只能 add 一个普通文件, 即 *.h / *.c / Makefile
git add filename

// 撤销add 
git restore --staged filename

// 提交, commit 后文件为未修改状态, 再修改内容, 为修改状态
git commit -m "20230826 name information"

// 提交后撤销修改
git restore filename

// 查看历史记录
git log --oneline --all --graph






git rm filename

git reset --hard commit_id
git reset --hard HEAD^

git reflog

git checkout -- filename   xxxxxxxxxx
```



## 分支

```shell
// 所有命令再 commit 之后, 修改之前运行

// 增加一个实验性功能
// 1. 新建一个分支
// 2. 切换到该分支
// 3. 新分支提交
// 3.1 不要, 切换回 master, 删除 子分支
// 3.2 想要, 切换回 master, 合并 子分支




// 新建分支 
git branch branch_name

// 切换分支
git checkout branch_name    xxxx

// 删除分支
git branch -D branch_name

// 合并分支
git merge branch-name




// 分支冲突

// A, B 改了同一个文件
// 1. 放弃
git merge --abort

// 2. 解决冲突
vim 冲突文件
git add 冲突文件
git commit -m "..."


// A 改文件, B 删文件
// 1. 想要
git add 冲突文件

// 2. 不想要
git rm 冲突文件






git branch
git branch -m old_branch_name new_branch_name
git branch -M old_branch_name new_branch_name


git checkout -b branch-name xxxx
git switch branch_name
git switch -c branch_name

git branch -d branch_name


```



## 同步

```shell
// 只能推送 master 分支 (同名分支)
// 云端分支在本地的引用 origin/master

// 推送
git push origin_name origin_branch_name

// 推送前其他人已推送
// 1.
// 将远程分支拉取到本地成为另一个分支
git fetch origin_name origin_branch_name
// 本地分支 合并 拉取到本地的远程分支
git merge origin_name/origin_branch_name

// 2. 合并 方法一 中的 fetch merge
git pull origin_name origin_branch_name




git remote add origin_name git@github.com:Xiao060/rep_name
git push -u origin_name origin_branch_name

git remote 
git remote -v

git remote rm origin_name
```



![image-20230826122102802](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/image-20230826122102802.png)

# ssh

```shell
ssh-keygen -t rsa -C "email"
ssh -T git@github.com

```

