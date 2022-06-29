# 常用命令

4. `git push\pull` 将本地仓库 push 到 Github / 将 Github 仓库同步到本地

# 常见问题
1.  **Failed to connect to github.com port 443 after 21081 ms: Timed out**

开启代理，关闭代理后重试

`git config --global https.proxy`

`git config --global --unset https.proxy`

2. **OpenSSL SSL_read: Connection was reset**

## 基础命令
- `git init` 创建本地仓库
- `git add -A / <filename>` 工作区 -> 暂存区
- `git commit -m "提交信息
"` 暂存区 -> 本地仓库
## 版本管理
- `git log` 提交日志
- `git reflog` 命令日志(提交 回退)
- `git status` 工作区 暂存区文件状态
- `git diff HEAD <filename>` 比较工作区 版本库最新版本的区别

- `git reset --hard <commit_id> ` 本地仓库 -> 暂存区
- `git reset HEAD <file_name> `  暂存区 -> 工作区 `git restore --staged <file_name>`
- `git checkout -- <filename>` 撤销修改 回到最近的 git add / git commit 状态  `git restore <file_name>`

## 远程仓库


## 分支管理
- `git branch` 查看分支
- `git branch <name>` 创建分支
- `git branch -d <name>` 删除分支
- `git switch <name>` 切换分支
- `git merge <name>` 合并分支<name> 到当前分支

