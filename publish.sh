#!/bin/sh

rm -rf build/intermediate-cpp/
mkdir -p build/intermediate-cpp/
cd build/intermediate-cpp/

git init
git remote add book https://DaveParillo@github.com/DaveParillo/intermediate-cpp.git
git pull --depth=1 book gh-pages
rm -rf [a-z]* _*

cd ../..
runestone build

cd build/intermediate-cpp/
# instruct github to process directories starting with underscores
touch .nojekyll
git add --all
git commit -m 'publish update to gh-pages'
#git merge --no-edit -s ours remotes/book/gh-pages
git push book master:gh-pages

