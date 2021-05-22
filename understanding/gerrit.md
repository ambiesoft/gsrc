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

# Download, Install and Run
## Download

```
mkdir ~/gerrit_testsite
cd ~/bin/gerrit/
wget https://gerrit-releases.storage.googleapis.com/gerrit-3.1.3.war
```

## Initialize
```
export GERRIT_SITE=~/gerrit_testsite
java -jar gerrit*.war init --batch --dev -d $GERRIT_SITE
```

## Update the listen URL
```
git config --file $GERRIT_SITE/etc/gerrit.config httpd.listenUrl 'http://localhost:8080'
```

## Restart the Gerrit service
```
$GERRIT_SITE/bin/gerrit.sh restart
```

## Viewing Gerrit
```
http://localhost:8080
```

# Create a repository in Gerrit
Run a command in the Gerrit host
```
cd ~/gerrit_testsite/git
mkdir merrit.git
cd merrit.git
git init --bare
git update-ref HEAD refs/heads/master   # this fails
```

# Clone from Gerrit and prepare
## Register public key
In the client environment, copy ./ssh/id_rsa.pub and paste it in the Gerrit's SSH-Keys

## Clone
```
git clone ssh://admin@192.168.3.99:29418/merrit.git
```

## copy commit-msg
```
$ scp -p -P 29418 admin@192.168.3.99:hooks/commit-msg .git/hooks/commit-msg
$ chmod u+x .git/hooks/commit-msg
$ grep -i change-id .git/hooks/commit-msg
```

## Modify and add and commit
```
vi first.txt
...
git add .
git commit -m 'my first commit'
```

## Push
```
$ git push origin HEAD:refs/for/master
Enumerating objects: 3, done.
Counting objects: 100% (3/3), done.
Writing objects: 100% (3/3), 264 bytes | 264.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0
remote: Processing changes: refs: 1, new: 1, done
remote:
remote: SUCCESS
remote:
remote:   http://192.168.3.99:8080/c/merrit/+/21 my first commit [NEW]
remote:
To ssh://192.168.3.99:29418/merrit.git
 * [new reference]   HEAD -> refs/for/master

```

## Open Url and Review

## Recommit and push
```
vi first.txt
...
git add .
git commit --amend
git push origin HEAD:refs/for/master
```

## Finish Review
Click 'Reivew' and 'SUBMIT'
