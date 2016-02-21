# renispace

## Git usage
Features should be developed on feature branches, then merged into master (using `--no-ff`).
This can be done locally, then the branch can be deleted.
If the feature branch is pushed to the public repository then it should not be deleted unless no-one else it using it.
One reason for sharing (large) feature branches is to use GitHub as a backup in the cloud.

### Git config
In order to set as default that git should no-fastforward local merges, but still fast forward pulls, follow the following steps (in the git BASH if using windows)

First change directory to somewhere in your local renispace git repository.
E.g. if using windows then type the following
```
cd c/path/to/your/local/renispace/repository
```
filling in `path/to/your/local/renispace/repository` with the path to your copy of the repo (forward slashes! and note C drive is mounted at `/c`)

Then run the following two commands:
```
git config merge.ff false
git config pull.ff pull
```

This will add configurations to your `.git/config` file, which is repository specific.

## Other useful things
See the GitHub [Markdown Basics](https://help.github.com/articles/markdown-basics/) page for an introduction on how to format this README file. 