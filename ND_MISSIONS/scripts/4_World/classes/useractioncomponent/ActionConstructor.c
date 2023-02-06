// Script File
modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);


		actions.Insert(alpLockVehicle);
		actions.Insert(alpUnlockVehicle);
		actions.Insert(alpCreateDuplicate);		
		actions.Insert(alpLockpicking);
		
		actions.Insert(alpActionOpenBarrel);
		actions.Insert(alpActionCloseBarrel);
		actions.Insert(alpActionDecontaminate);		

		actions.Insert(alpActionBuy);
		actions.Insert(alpActionSell);

		actions.Insert(alpActionATM);			
		actions.Insert(alpActionQuestBringMe);	

		actions.Insert(ActionDecontamineTarget);			
		actions.Insert(ActionDecontamineSelf);		
		
		actions.Insert(alpActionStartMission);	

		actions.Insert(alpActionServerConsole);	
		actions.Insert(alpActionServerConsoleLocked);	
		actions.Insert(alpActionServerConsoleLock);
		actions.Insert(alpActionServerConsoleUnlock);
		actions.Insert(alpActionServerConsoleRepair);
		
		actions.Insert(alpActionServerConsoleDownloadData);	
		actions.Insert(alpActionServerConsoleDeleteData);	
		
		
		actions.Insert(alpActionDigInRadioactiveBarrel);
	}
}