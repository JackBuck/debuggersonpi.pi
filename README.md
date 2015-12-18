# renispace

## Git usage
Features should be developed on feature branches, then merged into master (using `--no-ff`).
This can be done locally, then the branch can be deleted.
If the feature branch is pushed to the public repository then it should not be deleted.
One reason for sharing (large) feature branches is to use GitHub as a backup in the cloud.

The *Debugging* branch can be used for sharing bebugged code when asking for help.
It should be left in the same state as master when the problems have been solved:
```
git checkout Debugging
git merge master
git push origin Debugging
```
You may need to do a pull before you can push here.
Alternatively, if no-one is using it anymore it can be deleted locally
```
git branch --delete Debugging
```
and on the remote repository
```
git push origin --delete Debugging
```
I do not know what happens if someone deletes a branch on the remote repository which you are still working on!
(Though presumably you can just push it and hence create it on the remote repository again).
If more than one set of debugging is required at a time then another branch should be created and named appropriately.
