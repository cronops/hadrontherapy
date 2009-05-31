#----------------------------------------------------------
# Using Github.com code management

# Usage example 'make -f Makefile addPK'
# Init:
# A. fork git://github.com/kaitanie/hadrontherapy.git in Github to your own account
# B. only  once
#       git clone git@github.com:username/hadrontherapy.git

# When you start your session do 'make addPK' and 'make getPK' 

# [local edit]
# git diff
# git status
# git commit -a -m '[your comment]'  (add all changes)
# An alternatime method is to use a graphical commit tool:
# git gui (and then select the files to be committed using mouse,
# write a commit message, and press the "Commit" -button.
# git push (pushes the current branch to the default remote repository, the one you cloned from)
# If you need to push to an alternative user account, you can use:
# git push git@github.com:[username]/hadrontherapy.git

# Bad commits:
#
# Sometimes one creates a bad commit. There are several ways to fix
# it. The two most commonly used (and safest) options are:
#
# 1. Create additional "reverse commit"
#    git revert HEAD  (in case of bad commit this reverses it)
#
# 2. Amend (i.e. modify) the last commit
#
#    WARNING: Amending commits that have been PUSHED is EVIL. Don't do
#    it. If this is your case, then use option 1.
#
#    Use git add/rm or, in case of a beginner: git gui to fix the commit
#    git commit --amend   (replaces the latest commit with a new one)

pushAH:
	git push git@github.com:aatos/hadrontherapy.git

addPK:
	git remote add pekka git://github.com/kaitanie/hadrontherapy.git

getPK:
	git fetch pekka
	git merge pekka/master

run:
	$(G4INSTALL)/bin/$(G4SYSTEM)/Hadrontherapy
