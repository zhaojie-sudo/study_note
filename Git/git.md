# 常用命令

1.  `git init`  创建本地仓库
2. `git add -A / <filename>` 保存到暂存区
3. `git commit -m "提交信息"` 提交到本地仓库

# 常见问题
1.  **Failed to connect to github.com port 443 after 21081 ms: Timed out**

开启代理，关闭代理后重试

`git config --global https.proxy`

`git config --global --unset https.proxy`