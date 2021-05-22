# Change-Id
Gerrit identifies a conceptual change with a footer in the commit message. Because `git commit --amend` changes the SHA-1.
```
Change-Id: I9e29f5469142cc7fce9e90b0b09f5d2186ff0990
```
Gerrit provides a client-side message hook to automatically add to commit messages when necessary.

# Life Cycle
```
git clone ssh://gerrithost:29418/RecipeBook.git RecipeBook
```

Command to add a Change-Id to his commits.
```
scp -p -P 29418 gerrithost:hooks/commit-msg RecipeBook/.git/hooks/
chmod u+x .git/hooks/commit-msg
```

Commit and push
```
$ <work>
$ git commit
[master 3cc9e62] Change to a proper, yeast based pizza dough.
 1 file changed, 10 insertions(+), 5 deletions(-)
$ git push origin HEAD:refs/for/master
Counting objects: 3, done.
Delta compression using up to 8 threads.
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 532 bytes | 0 bytes/s, done.
Total 3 (delta 0), reused 0 (delta 0)
remote: Processing changes: new: 1, done
remote:
remote: New Changes:
remote:   http://gerrithost/#/c/RecipeBook/+/702 Change to a proper, yeast based pizza dough.
remote:
To ssh://gerrithost:29418/RecipeBook
 * [new branch]      HEAD -> refs/for/master
```

```
git push origin HEAD:refs/for/master
```
これの意味。originはリモートリポジトリ、HEAD:refs/for/masterはrefspec。refspecとはローカルのrefとリモートのrefを関連付けるもの。refとは./git/refs/配下にあるオブジェクトを指すポインタ。つまりこのコマンドによりoriginのrefs/for/masterにローカルのHEADがpushされる。

Gerritはこのrefをレビュー用のrefとして使う。このrefにpushされるとGerritは以下のrefを作成する。

```
refs/changes/[CD]/[ABCD]/[EF]
```
* [CD] is the last two digits of the change number
* [ABCD] is the change number
* [EF] is the patch set number

このchangeをfetchするには以下のコマンド
```
git fetch https://[GERRIT_SERVER_URL]/[PROJECT] refs/changes/[XX]/[YYYY]/[ZZ] \
&& git checkout FETCH_HEAD
```

chromiumのGerritだと以下のように持ってくる。
```
git pull https://chromium.googlesource.com/chromium/src refs/changes/58/2903858/5
```
