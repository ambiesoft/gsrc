# modify and commit
1. Create branch
1. Mark the associated crbug as "started"
1. git checkout \<branch>
1. Check that common targets build correctly:
	* chrome
	* unit_tests
	* browser_tests
1. Run chrome for testing
	* Edge case
	* Guest mode
1. Run ```git cl format --js```. The ```--js``` option also formats JavaScript changes.
1. ```git diff``` to review all of the changes. ```git upstream-diff``` is what you will be uploaded to Gerrit.
1. ```git add```
1. ```git commit```
1. Format of commit message:
```text
Summary of change (one line)

Longer description of change addressing as appropriate: why the change
is made, context if it is part of many changes, description of previous
behavior and newly introduced differences, etc.

Long lines should be wrapped to 72 columns for easier log message
viewing in terminals.

Bug: 123456
```
1. ```git rebase-update``` to rebase and resolve any merge conflict errors. If conflict, Fix them and run ```git rebase --continue```. Before building, don't forget to ```gclient sync -D```.
1. ```git cl upload``` to send the patch to Gerrit.
1. ```git cl issue``` returns none if this CL is new.
1. Check the CL again in Gerrit
	1. ```git cl web``` to go to the Gerrt URL associated with the current branch.
1. Click 'CQ Dry Run'. Fix any errors.
1. Add reviews
	1. Click 'Find Owners' to find file owners to review your code and instruct them about which parts you want them to focus on. Add anyone else to review your code.
	1. If you have multiple reviewers, provide a message indicating what you expect from each reviewer. Otherwise people might assume their input is not required or waste time with redundant reviews.
	1. The blame functionality in Code Search is a good way to identify reviewers who may be familiar with the parts of code your CL touches. 
	1. One reviewer for one file.
	1. For your CL to land, you need an approval from an owner for each file you've changed.
1. Click 'Start Review' to begin the actual review process. Until you press this button, nobody will look at your change. Once pressed, you'll have the opportunity to include an additional message in the notification sent to your reivewers.
1. Implement feedback from your reviewers
	1. Reply to all comments from the reviewers on Gerrit and mark all resolved issues as resolved (clicking 'Done' or 'Ack' will do this automatically). Click 'Reply' to ensure that your reviewers recieve a notification. Doing this signals that your CL is ready for review agein, since the assumption is that your CL is not ready for reviewe until you hit reply.
	1. To upload new patch sets that address comments from the reviewers, simply commit more changes to your local branch and run ```git cl``` upload again.
	1. If your change is simple and you feel confident that reviewer will approve your CL on the next iteration, you can set 'Auto-Submit+1'. The CL will proceed to the next step automatically after approval. This feature is useful if your reviewer is in a different time zone and you want to land the CL sooner. Setting this flag also puts the onus on your reviewer to land the CL.
	
1. Land your CL
	1. Once you have obtained a 'Looks Good To Me(LGTM)', which is reflected by a 'Code-Review+1' in Gerrit, from at least one owner for each file, the you have the minimum prerequisite to land your changes. It may be helpful to wait for all of your reviewers to approve your changes as well, even if they're not owners.
	1. 'Submit to CQ' to try your change in the commit queue(CQ), which will land it if successful.
	1. Monitor 'Chromium tree' for about a day after your CL lands.
	1. If the Sheriff or anyone else brings any failures to your attention, revert the CL first and ask questions later. Gerrit cat automatically generate revert CLs.
1. Cleanup
	1. After your CL is landed, you can use ```git rebase-update``` or ```git cl archive``` to clean up your local branches. These commands will automatically delete merged branches.
	1. Mark the associated crbug as 'fixed'.
	
