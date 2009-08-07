#----------------------------------------------------------
# Using Github.com code management
#
# http://github.com/kaitanie/hadrontherapy (get official version from coordinator)
# http://github.com/aatos/hadrontherapy (AH)
#
# Usage example 'make -f Makefile addPK'
# Init:
# A. fork http://github.com/kaitanie/hadrontherapy in Github to your own account
#    using the Github web interface
# B. only  once
#       git clone git@github.com:username/hadrontherapy.git

# When you start your session do 'make addPK' and 'make getPK' 

# [local edit]
# git diff
# git status
# [git add newfile , clean extra files]
# git commit -a -m '[your comment]'  (add all changes)
# git push

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

exfor:
	root RootScripts/iaeaBenchmark/readExfor.C
pushAH:
	git push git@github.com:aatos/hadrontherapy.git

pushGD:
	git push git@github.com:Gillis/hadrontherapy.git

addPK:
	git remote add pekka git://github.com/kaitanie/hadrontherapy.git

getPK:
	git fetch pekka
	git merge pekka/master

run:
	$(G4WORKDIR)/bin/$(G4SYSTEM)/Hadrontherapy defaultMacro.mac

iaea:
	$(G4WORKDIR)/bin/$(G4SYSTEM)/Hadrontherapy iaea.mac

r: # 
	Hadrontherapy macro/iaea.mac
	echo -e '\a'
	root -l RootScripts/iaeaBenchmark/fragmentEnergy.C++
	root -l RootScripts/iaeaBenchmark/fragmentEnergyWithAngularDistribution.C
	
raFragments: # run only analysis
	root -l RootScripts/iaeaBenchmark/fragmentEnergy.C

raAngular: #produce the angular distribution plots of the fragments
	root RootScripts/iaeaBenchmark/fragmentAngularDistribution.C

raAngularHistogram: #produce the angular distribution in a histogram with equal bins
	root RootScripts/iaeaBenchmark/fragmentAngularDistributionHistogram.C


raAngularEnergy: #produce the angular distribution plots of the fragments
	root RootScripts/iaeaBenchmark/fragmentEnergyDistributionDifferentAngles.C

r0: # run in AH environment

	Hadrontherapy defaultMacro.mac

clean:
	rm -f $(d).pdf $(d).ps *.out $(d)_*.eps $(d).asy
