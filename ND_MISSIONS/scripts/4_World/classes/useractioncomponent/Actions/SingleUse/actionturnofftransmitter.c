
modded class ActionTurnOffTransmitter: ActionTurnOffWhileInHands
{

		
	override void OnExecuteServer(ActionData action_data)
	{
		super.OnExecuteServer(action_data);
				
		PersonalRadio radio;
		if ( Class.CastTo( radio, action_data.m_MainItem ) ){
			radio.SetWorkingStateALP(false);	
		}
	}
}

modded class ActionTurnOnTransmitter : ActionTurnOnWhileInHands
{

		
	override void OnExecuteServer(ActionData action_data)
	{
		super.OnExecuteServer(action_data);
		PersonalRadio radio;
		if ( Class.CastTo( radio, action_data.m_MainItem ) ){
			radio.SetWorkingStateALP(true);	
		}
	}
}