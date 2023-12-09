
void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}

	
}

class CustomMission: MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			float rndHlt = Math.RandomFloat( 0.10, 0.35 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
		Class.CastTo( m_player, playerEnt );

		GetGame().SelectPlayer( identity, m_player );

		return m_player;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;
		player.GetStatWater().Set(1350);
        player.GetStatEnergy().Set(1350);
		
		
		string trousersArray[] = {"Jeans_Black","Jeans_Blue","Jeans_Grey","Jeans_Green"}; //list of trousers
		string topsArray[] = {"TShirt_Blue","TShirt_Red","TShirt_Green","TShirt_Black"}; //list of tops
		string feetArray[] = {"AthleticShoes_Blue","AthleticShoes_Black","AthleticShoes_Brown","AthleticShoes_Green"}; //list of shoes
		int rndItem = Math.RandomInt( 1, 4 ); //random number
		
		player.RemoveAllItems(); // clear inventory of all items before spawning new clothing

		player.GetInventory().CreateInInventory(trousersArray[rndItem]);//pick random trousers from array
		player.GetInventory().CreateInInventory(topsArray[rndItem]);//pick random top from array
		player.GetInventory().CreateInInventory(feetArray[rndItem]);//pick random shoe from array


		itemClothing = player.FindAttachmentBySlotName( "Body" );
		if ( itemClothing )
		{
			SetRandomHealth( itemClothing );
		}
		
		itemClothing = player.FindAttachmentBySlotName( "Legs" );
		if ( itemClothing )
		{
			//SetRandomHealth( itemEnt );
			//SetRandomHealth( itemClothing );
			
			//itemEnt = itemClothing.GetInventory().CreateInInventory( "Rag" );
			//if ( Class.CastTo( itemBs, itemEnt ) )
			//	itemBs.SetQuantity( 2 );

			//string chemlightArray[] = { "Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red" };
			//int rndIndex = Math.RandomInt( 0, 4 );
			//itemEnt = itemClothing.GetInventory().CreateInInventory( chemlightArray[rndIndex] );
			//SetRandomHealth( itemEnt );

			//rand = Math.RandomFloatInclusive( 0.0, 1.0 );
			//if ( rand < 0.35 )
			//	itemEnt = player.GetInventory().CreateInInventory( "Apple" );
			//else if ( rand > 0.65 )
			//	itemEnt = player.GetInventory().CreateInInventory( "Pear" );
			//else
			//	itemEnt = player.GetInventory().CreateInInventory( "Plum" );

			SetRandomHealth( itemEnt );
			
		}
			itemClothing = player.FindAttachmentBySlotName( "Feet" );	
			if (itemClothing)
			{
			}
			
	}
	
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}