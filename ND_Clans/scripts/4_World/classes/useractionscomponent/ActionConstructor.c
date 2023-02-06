// Script File

modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		
		actions.Insert(alpAddFriendAction);


		actions.Insert(alpActionDisassemblePlotPole);
		actions.Insert(alpActionManagePlotPole);

		
		actions.Insert(alpActionLockDoors);
		actions.Insert(alpActionUnlockDoors);
		
		actions.Insert(alpActionClaimBed);
		actions.Insert(alpActionReleaseBed);
		
		actions.Insert(alpActionIgniteDynamite);
	}
}

