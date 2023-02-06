class alpMessagesLocationLabel 
{
	ref map<string,ref vector>					alp_Location = new  map<string,ref vector>;
	
	
	void alpMessagesLocationLabel()
	{
		string mise;
		
		if ( GetGame() && GetGame().IsServer() )
		{
			GetDayZGame().GetWorldName(mise );			
		}
		else
		{
			mise =GetDayZGame().GetMissionPath();		
		}
		
		mise.ToLower();
		
		if (mise.Contains("banov") )
		{
			alp_Location.Insert("Banovce nad Bebravou","6167.08 0 1713.74");
			alp_Location.Insert("Sliezska Osada","2147.81 0 2054.68");
			alp_Location.Insert("Dvorec","3753.73 0 665.95");
			alp_Location.Insert("Pod horom luky","898.18 0 812.37");
			alp_Location.Insert("Velke Dzrkovce","495.59 0 2854.75");
			alp_Location.Insert("Ruskovce","1232.07 0 4184.46");
			alp_Location.Insert("Vlckovo","2179.93 0 6356.07");
			alp_Location.Insert("Military Obsidian","1268.67 0 7260.73");			
			alp_Location.Insert("Podluzany","4794.96 0 6287.35");
			alp_Location.Insert("Timoradza","4432.97 0 11147.08");
			alp_Location.Insert("Krasna Ves","4130.25 0 13740.35");
			alp_Location.Insert("Alica Airport","4918.88 0 4752.14");
			alp_Location.Insert("Banovce Industrial","7428.32 0 1972.52");
			alp_Location.Insert("Banovce North","5636.54 0 2677.21");
			alp_Location.Insert("Latcovce","12984.79 0 509.37");
			alp_Location.Insert("Miezgovce","9924.72 0 1645.75");
			alp_Location.Insert("Uhrovec","11793.23 0 4110.60");
			alp_Location.Insert("Zitna Radisa","12110.23 0 6542.85");
			alp_Location.Insert("Omastina","14080.28 0 6782.81");
			alp_Location.Insert("Ksinna","12712.66 0 10923.14");	
			alp_Location.Insert("R.A.B.B.I.T.","13322.22 0 11516.56");				
			alp_Location.Insert("Zavada pod Ciernym vrchom","13096.55 0 12488.74");
			alp_Location.Insert("Military Tisovik","12038.90 0 14996.67");
			alp_Location.Insert("Slatina nad Bebravou","6535.99 0 13704.77");
			alp_Location.Insert("Kopec","7120.91 0 12068.48");
			alp_Location.Insert("Trebichava","9083.18 0 12233.21");
			alp_Location.Insert("OverGrown Military","8175.32 0 9814.12");
			alp_Location.Insert("Lutov","7701.94 0 7690.78");
			alp_Location.Insert("Prusy","6207.01 0 5616.56");
			alp_Location.Insert("Hrabice Airport","2106.20 0 11754.69");
			alp_Location.Insert("Negans Sanctuary","2019.56 0 9466.26");
			alp_Location.Insert("Vadna nadrz Prusy","6916.83 0 4302.70");
			alp_Location.Insert("Rybarska Basta","6910.05 0 3544.76");
			alp_Location.Insert("Horne Nastice","8840.67 0 3139.17");
			alp_Location.Insert("Biscupice","5023.79 0 481.70");
			alp_Location.Insert("Jankov vrsok","13842.32 0 3739.47");
			alp_Location.Insert("Liana","14550.58 0 12648.34");
			alp_Location.Insert("Catherine Antena","14654.97 0 15048.99");
			alp_Location.Insert("Mastodon Geothermal Park","13827.71 0 9101.39");
			alp_Location.Insert("Dubnicka","9290.79 0 6606.18");
			alp_Location.Insert("Pepelova Military","328.51 0 5931.32");
			alp_Location.Insert("Hotel Delta","673.50 0 7160.09");		
			alp_Location.Insert("Mala","713.17 0 11082.36");
			alp_Location.Insert("Hvozdy","7358.38 0 13747.66");
			alp_Location.Insert("Radio North Exile","10897.59 0 12629.55");
			alp_Location.Insert("EastHaven","14520.83 0 9679.24");
			alp_Location.Insert("Ceremor Wooden Pile","6507.64 0 15045.34");
			alp_Location.Insert("Joito Summer Camp","7687.20 0 11019.20");
			alp_Location.Insert("Petra","3540.47 0 9942.84");
			alp_Location.Insert("Tower Orion","13087.61 0 10275.88");
			alp_Location.Insert("Nad Rybnikami","465.77 0 14635.57");
			alp_Location.Insert("Motesice","859.31 0 12900.46");
			alp_Location.Insert("Kastiel Panny","816.51 0 13381.22");
			alp_Location.Insert("Dolne Motesice","339.99 0 11671.69");
			alp_Location.Insert("Bobot","1290.95 0 10638.66");
			alp_Location.Insert("TopeREC","827.47 0 9050.76");
			alp_Location.Insert("Hornany","1751.29 0 7768.22");
			alp_Location.Insert("Dezerice","3036.28 0 6210.59");
			alp_Location.Insert("Prison Veronika","2294.10 0 4910.30");
			alp_Location.Insert("Horne Ozorovce","4378.18 0 3453.68");			
		}
		
		if (mise.Contains("namalsk") )
		{
			
			alp_Location.Insert("Vorkuta","6815.31 0 11209.87");
			alp_Location.Insert("Jalovisko","8266.36 0 10752.36");
			alp_Location.Insert("Lubjansk","4470.35 0 11148.92");
			alp_Location.Insert("Nemsk","9079.79 0 10120.21");
			alp_Location.Insert("Norinsk","3941.35 0 7544.74");
			alp_Location.Insert("Brensk","4336.73 0 4732.12");
			alp_Location.Insert("Tara harbor","7821.74 0 7602.95");
			alp_Location.Insert("Sebjan","5226.74 0 8631.66");
			alp_Location.Insert("Alakit","5840.13 0 10749.62");
			alp_Location.Insert("Norinsk pass","4503.95 0 7165.37");
			alp_Location.Insert("warehouses","4693.05 0 8893.82");
			alp_Location.Insert("Sibirskiy-2119","3956.97 0 10273.76");
			alp_Location.Insert("SKAT-12","11949.06 0 11981.88");
			alp_Location.Insert("TF Bering outpost","1226.79 0 11819.35");
			alp_Location.Insert("BK-T12","4085.12 0 9217.31");
			alp_Location.Insert("BK-T08","3947.6 0 9965.89");
			alp_Location.Insert("BK-T07","4418 0 10722.28");
			alp_Location.Insert("BK-M06","4860.26 0 10837.92");
			alp_Location.Insert("BK-L16","5999.54 0 6694.98");
			alp_Location.Insert("BK-L01","4155.45 0 6652.78");
			alp_Location.Insert("Athena Research Institute","4274.22 0 8063.98");
			alp_Location.Insert("Athena-1","3791.32 0 8214");
			alp_Location.Insert("Athena-2","4988.41 0 6613.71");
			alp_Location.Insert("BK-L02","3428.75 0 6737.17");
			alp_Location.Insert("Sebjan valley","5530.7 0 8851.62");
			alp_Location.Insert("Sebjan dam","5716.67 0 9851.8");
			alp_Location.Insert("Sebjan uranium mine","4866.52 0 7976.46");
			alp_Location.Insert("refugee camp","7307.59 0 10523.8");
			alp_Location.Insert("refugee camp","5155.63 0 8954.76");
			alp_Location.Insert("C-130J Mohawk","3188.87 0 7531.85");
			alp_Location.Insert("airfield","6232.39 0 9381.41");
			alp_Location.Insert("factory","6502.75 0 9297.01");
			alp_Location.Insert("factory","5802.62 0 8670.34");
			alp_Location.Insert("factory","7662.34 0 8731.29");
			alp_Location.Insert("sawmill","7040.35 0 5813.56");
			alp_Location.Insert("hospital","7270.08 0 7940.52");
			alp_Location.Insert("Brensk bridge","5014.98 0 6079.24");
			alp_Location.Insert("Tara bridge","6433.99 0 5840.13");
			alp_Location.Insert("Tara strait","6335.54 0 8109.3");
			alp_Location.Insert("Brensk bay","5168.13 0 5365.04");
			alp_Location.Insert("Seraja bay","3386.56 0 5552.58");
			alp_Location.Insert("Lubjansk bay","5111.87 0 10237.81");
			alp_Location.Insert("Nemsk bay","7974.9 0 9687.71");
			alp_Location.Insert("Sebjan reservoir","6090.18 0 10051.84");
			alp_Location.Insert("Sebjan marsh","6874.7 0 9947.13");
			alp_Location.Insert("Brensk marsh","5957.34 0 5666.66");
			alp_Location.Insert("Tara","7265.39 0 7040.35");
			alp_Location.Insert("Nitija","5262.68 0 7190.38");
			alp_Location.Insert("Seraja","4186.7 0 6606.68");
			alp_Location.Insert("Ledjanaja","2989.61 0 6473.06");
			
		}
				
		if (mise.Contains("cherna") || mise.Contains("Cherna")){
			alp_Location.Insert("Balota","4390 0 2410");
			alp_Location.Insert("Balota Airstrip","5030 0 2360");
			alp_Location.Insert("Bashnya","4160 0 11750");
			alp_Location.Insert("Bay Mutnaya","5630 0 1950");
			alp_Location.Insert("Bay Tikhaya","1190 0 2190");
			alp_Location.Insert("Bay Zelenaya","11140 0 3090");
			alp_Location.Insert("Belaya Polana","14150 0 15000");
			alp_Location.Insert("Berezhki","15150 0 13820");
			alp_Location.Insert("Berezino","11860 0 8990");
			alp_Location.Insert("Black Forest","9080 0 7560");
			alp_Location.Insert("Black Lake","13360 0 11900");
			alp_Location.Insert("Black Mtn","10250 0 11980");
			alp_Location.Insert("Bogatyrka","1500 0 8940");
			alp_Location.Insert("Bor","3320 0 4010");
			alp_Location.Insert("Cap Golova","8350 0 2440");
			alp_Location.Insert("Cernaya Polana","12200 0 13670");
			alp_Location.Insert("Chernogorsk","6570 0 2450");
			alp_Location.Insert("Chernogorsk Factory","6410 0 2710");
			alp_Location.Insert("Chyornaya Bay","7710 0 3090");
			alp_Location.Insert("Crown Castle","1430 0 9220");
			alp_Location.Insert("Deep Lake","1850 0 14860");
			alp_Location.Insert("Devil's Castle","6910 0 11370");
			alp_Location.Insert("Dichina Military","4620 0 8280");
			alp_Location.Insert("Dobroe","13100 0 14950");
			alp_Location.Insert("Dolina","11330 0 6650");
			alp_Location.Insert("Drakon Island","11190 0 2490");
			alp_Location.Insert("Drozhino","3450 0 4930");
			alp_Location.Insert("Dubky","6650 0 3670");
			alp_Location.Insert("Dubrovka","10400 0 9800");
			alp_Location.Insert("Dubrovka Vyshnaya","9950 0 10390");
			alp_Location.Insert("Electrozavodsk","10500 0 2340");
			alp_Location.Insert("Gnome Castle","7410 0 9110");
			alp_Location.Insert("Gorka","9650 0 8810");
			alp_Location.Insert("Green Mtn","3740 0 6010");
			alp_Location.Insert("Grishino","6020 0 10260");
			alp_Location.Insert("Grozovoy Pass","3240 0 15290");
			alp_Location.Insert("Guba","14610 0 13280");
			alp_Location.Insert("Guglovo","8410 0 6690");
			alp_Location.Insert("Gvozdno","8710 0 11900");
			alp_Location.Insert("Kabanino","5300 0 8560");
			alp_Location.Insert("Kamenka","1890 0 2160");
			alp_Location.Insert("Kamensk","6630 0 14470");
			alp_Location.Insert("Kamyshovo","12170 0 3450");
			alp_Location.Insert("Karmanovka","12520 0 14680");
			alp_Location.Insert("Khelm","12290 0 10790");
			alp_Location.Insert("Klen Mtn","11490 0 11330");
			alp_Location.Insert("Komarovo","3620 0 2340");
			alp_Location.Insert("Kozlova Mtn","8830 0 2860");
			alp_Location.Insert("Kozlovka","4450 0 4580");
			alp_Location.Insert("Krasnoe","6490 0 14980");
			alp_Location.Insert("Krasnostav","11230 0 12220");
			alp_Location.Insert("Krasnostav Airstrip","12020 0 12490");
			alp_Location.Insert("Krutoy Cap","13620 0 3890");
			alp_Location.Insert("Kumyrna","8400 0 6030");
			alp_Location.Insert("Lopatino","2750 0 9990");
			alp_Location.Insert("Mamino","7980 0 13060");
			alp_Location.Insert("Mogilevka","7500 0 5240");
			alp_Location.Insert("Msta","11260 0 5510");
			alp_Location.Insert("Myshkino","2060 0 7430");
			alp_Location.Insert("Myshkino Military","1270 0 7230");
			alp_Location.Insert("Nadezhdino","5820 0 4760");
			alp_Location.Insert("Nagornoe","9330 0 14670");
			alp_Location.Insert("Nizhnoye","12900 0 8040");
			alp_Location.Insert("Novaya Petrovka","3470 0 12990");
			alp_Location.Insert("Novaya Trainyard","3530 0 12580");
			alp_Location.Insert("Novodmitrovsk","11600 0 14700");
			alp_Location.Insert("Novoselky","6050 0 3290");
			alp_Location.Insert("Novy Sobor","7160 0 7690");
			alp_Location.Insert("NWA","4644 0 10104");
			alp_Location.Insert("Olha","13320 0 12890");
			alp_Location.Insert("Oreshka Pass","9880 0 6010");
			alp_Location.Insert("Orlovets","12140 0 7280");
			alp_Location.Insert("Orlovets Factory","11490 0 7590");
			alp_Location.Insert("Otmel Island","11640 0 3100");
			alp_Location.Insert("Pavlovo","1630 0 3850");
			alp_Location.Insert("Pavlovo Military","2100 0 3290");
			alp_Location.Insert("Pogorevka","4380 0 6410");
			alp_Location.Insert("Polana","10680 0 8090");
			alp_Location.Insert("Polesovo","5820 0 13490");
			alp_Location.Insert("Prigorodki","7980 0 3300");
			alp_Location.Insert("Prud Lake","6630 0 9290");
			alp_Location.Insert("Pulkovo","4900 0 5650");
			alp_Location.Insert("Pusta","9180 0 3860");
			alp_Location.Insert("Pustoshka","2990 0 7810");
			alp_Location.Insert("Ratnoe","6310 0 12710");
			alp_Location.Insert("Rify","13780 0 11230");
			alp_Location.Insert("Rog Castle","11260 0 4290");
			alp_Location.Insert("Rogovo","4730 0 6780");
			alp_Location.Insert("Romashka","8150 0 11020");
			alp_Location.Insert("Schadenfreude Island","24000 0 0");
			alp_Location.Insert("Severograd","7890 0 12580");
			alp_Location.Insert("Shakhovka","9670 0 6500");
			alp_Location.Insert("Silence Lake","1200 0 6510");
			alp_Location.Insert("Sinystok","1450 0 11920");
			alp_Location.Insert("Skalisty Island","13660 0 2960");
			alp_Location.Insert("Smirnovo","11630 0 15020");
			alp_Location.Insert("Solnichniy","13470 0 6240");
			alp_Location.Insert("Solnichniy Factory","13070 0 7160");
			alp_Location.Insert("Sosnovka","2510 0 6370");
			alp_Location.Insert("Sosnovy Pass","2740 0 6760");
			alp_Location.Insert("Staroye","10160 0 5460");
			alp_Location.Insert("Stary Sobor","6070 0 7750");
			alp_Location.Insert("Stary Yar","4940 0 15070");
			alp_Location.Insert("Prison Island","2610 0 1310");
			alp_Location.Insert("Svergino","9530 0 13730");
			alp_Location.Insert("Svetlojarsk","13930 0 13230");
			alp_Location.Insert("Three Valleys","12840 0 5500");
			alp_Location.Insert("Tisy","3410 0 14810");
			alp_Location.Insert("Tisy Military","1680 0 14120");
			alp_Location.Insert("Topolniki","2820 0 12370");
			alp_Location.Insert("Troitskoe","7560 0 13520");
			alp_Location.Insert("Troitskoe Military","7870 0 14680");
			alp_Location.Insert("Tulga","12810 0 4460");
			alp_Location.Insert("Turovo","13580 0 14130");
			alp_Location.Insert("Vavilovo","2210 0 11020");
			alp_Location.Insert("Veresnik Mtn","4440 0 8080");
			alp_Location.Insert("Vybor","3800 0 8840");
			alp_Location.Insert("Vyshnoye","6530 0 6090");
			alp_Location.Insert("Vysotovo","5620 0 2560");
			alp_Location.Insert("Willow Lake","13250 0 11610");
			alp_Location.Insert("Zabolotye","1160 0 10010");
			alp_Location.Insert("Zaprudnoe","4930 0 13030");
			alp_Location.Insert("Zelenogorsk","2710 0 5390");
			alp_Location.Insert("Zub Castle","6540 0 5590");
			alp_Location.Insert("Zvir","480 0 5200");
			}
		if (mise.Contains("enoch") || mise.Contains("Enoch"))
		{		
			alp_Location.Insert("Bielawa","1451.05 0 9718.19");
			alp_Location.Insert("Lukow","3538.15 0 11907.65");
			alp_Location.Insert("Gliniska","4998.57 0 9902.59");
			alp_Location.Insert("Brena","6591.83 0 11210.65");
			alp_Location.Insert("Tarnow","9325.14 0 10856.68");
			alp_Location.Insert("Sitnik","11565.4 0 9521.27");
			alp_Location.Insert("Borek","9794.76 0 8478.9");
			alp_Location.Insert("Zapadlisko","8146.8 0 8679.71");
			alp_Location.Insert("Nidek","6097.21 0 8013.19");
			alp_Location.Insert("Topolin","1864.4 0 7327.12");
			alp_Location.Insert("Adamów","3109.94 0 6801.25");
			alp_Location.Insert("Muratyn","4611 0 6350.38");
			alp_Location.Insert("Radunin","7326.34 0 6432.43");
			alp_Location.Insert("Lembork","8808.64 0 6597.3");
			alp_Location.Insert("Gieraltów","11284.1 0 4342.98");
			alp_Location.Insert("Nadbór","6164.41 0 4096.84");
			alp_Location.Insert("Zalesie","895.48 0 5504.91");
			alp_Location.Insert("Huta","5156.41 0 5490.85");
			alp_Location.Insert("Radacz","4008.55 0 7903.01");
			alp_Location.Insert("Olszanka","4780.56 0 7592.8");
			alp_Location.Insert("Lipina","5951.09 0 6791.09");
			alp_Location.Insert("Kolembrody","8426.54 0 11936.56");
			alp_Location.Insert("Karlin","10087.78 0 6907.51");
			alp_Location.Insert("Sobotka","6291.78 0 10187.8");
			alp_Location.Insert("Roztoka","7705.32 0 5275.18");
			alp_Location.Insert("Polana","3294.35 0 2113.67");
			alp_Location.Insert("Dolnik","11336.45 0 639.18");
			alp_Location.Insert("Sowa","11671.67 0 12008.45");
			alp_Location.Insert("Krsnik","7863.94 0 10035.43");
			alp_Location.Insert("Dambog","582.14 0 1118.95");
			alp_Location.Insert("Skala","3005.24 0 1942.54");
			alp_Location.Insert("Swarog","4875.89 0 2207.44");
			alp_Location.Insert("Rodzanica","8894.6 0 2037.87");
			alp_Location.Insert("Bagno","11830.29 0 11120.79");
			alp_Location.Insert("Wrzeszcz","9059.47 0 4383.62");
			alp_Location.Insert("Drewniki","5847.95 0 5069.68");
			alp_Location.Insert("Kulno","11127.04 0 2386.37");
			alp_Location.Insert("Hrud","6446.49 0 9357.96");
			alp_Location.Insert("Jantar","3530.33 0 8932.89");
			alp_Location.Insert("Grabinskie","11259.87 0 10981.7");
			alp_Location.Insert("Wolisko","12372.58 0 10862.93");
			alp_Location.Insert("Sitnickie","11416.15 0 10415.97");
			alp_Location.Insert("Grabin","10661.33 0 11011.39");
			alp_Location.Insert("Branzów Castle","1088.48 0 11352.08");
			alp_Location.Insert("Piorun","648.56 0 12095.18");
			alp_Location.Insert("Jezurów","2091.79 0 2347.3");
			alp_Location.Insert("Tymbark","2906.78 0 1213.5");
			alp_Location.Insert("Hedryków","4514.89 0 4788.38");
			alp_Location.Insert("Widok","10244.06 0 2143.36");
			alp_Location.Insert("Kopa","5535.39 0 8721.13");
		}
		if (mise.Contains("deerisle") )
		{
			alp_Location.Insert("Paris Island","2880.64 0 3903.84");
			alp_Location.Insert("Airfield","5508.05 0 3555.0");
			alp_Location.Insert("Devils Eye","6654.23 0 3472.0");
			alp_Location.Insert("Starks Castle","5771.42 0 2372.25");
			alp_Location.Insert("Prison","5470.16 0 657.96");
			alp_Location.Insert("Kushville","7533.6 0 3910.21");
			alp_Location.Insert("Milo","6545.98 0 3922.54");
			alp_Location.Insert("Sunset Cross","6580.82 0 6382.9");
			alp_Location.Insert("Asheville","7311.23 0 2607.06");
			alp_Location.Insert("Warren Cove","7050.68 0 5360.82");
			alp_Location.Insert("Oceanville","10258.63 0 4879.96");
			alp_Location.Insert("Stonington","6829.42 0 1860.68");
			alp_Location.Insert("Greenville","4744.71 0 1492.5");
			alp_Location.Insert("Sandy Bay","5347.71 0 7584.46");
			alp_Location.Insert("Oldfield","6114.19 0 6921.69");
			alp_Location.Insert("Sheep Island","11941.83 0 3882.23");
			alp_Location.Insert("Smallville","10355.04 0 4360.0");
			alp_Location.Insert("Horizon","4139.5 0 15461.3");
			alp_Location.Insert("Deepwater","1668.19 0 12694.2");
			alp_Location.Insert("Rogue Wave","2144.84 0 14620.29");
			alp_Location.Insert("Groots Hill","7618.3 0 4822.98");
			alp_Location.Insert("Pauls View","9561.75 0 3716.43");
			alp_Location.Insert("Hazelands","4538.48 0 2693.84");
			alp_Location.Insert("Stonington Harbor","6839.3 0 1422.04");
			alp_Location.Insert("Industrial","6787.05 0 2376.03");
			alp_Location.Insert("Suburbs South","7206.72 0 1492.36");
			alp_Location.Insert("Suburbs North","6335.53 0 2043.49");
			alp_Location.Insert("Camp Eagle","8778.02 0 3733.29");
			alp_Location.Insert("Camp Wolf","5478.76 0 1056.63");
			alp_Location.Insert("Scouts Camp","4930.44 0 2049.25");
			alp_Location.Insert("Scouts Camp","8476.94 0 5305.38");
			alp_Location.Insert("Fishers Camp","10343.42 0 5586.74");
			alp_Location.Insert("Portland","6100.01 0 14802.42");
			alp_Location.Insert("Georgestown","4716.63 0 4469.67");
			alp_Location.Insert("Westbrook","3302.84 0 6372.34");
			alp_Location.Insert("Swamp","3801.86 0 9049.32");
			alp_Location.Insert("Old Town","1840.61 0 9070.56");
			alp_Location.Insert("Mountainville","7291.04 0 8511.83");
			alp_Location.Insert("Camp Bear","8865.93 0 5988.4");
			alp_Location.Insert("RCFI","3732.7 0 8812.97");
			alp_Location.Insert("Mine","11148.46 0 2273.53");
			alp_Location.Insert("Crotch Island","10812.11 0 2584.11");
			alp_Location.Insert("Area 42","13379.05 0 9849.64");
			alp_Location.Insert("Rockenheim Circuit","10060.04 0 11060.91");
			alp_Location.Insert("Waldoboro","8730.99 0 9163.4");
			alp_Location.Insert("East Harbor","11363.58 0 10103.37");
			alp_Location.Insert("Woodworking Industrial","4446.97 0 12078.14");
			alp_Location.Insert("Swanville","5289.25 0 12384.22");
			alp_Location.Insert("Bayville","10178.36 0 12011.76");
			alp_Location.Insert("PearPlantation","9570.54 0 7613.58");
			alp_Location.Insert("Montville","9370.89 0 8062.24");
			alp_Location.Insert("Eastbrook","10417.4 0 7851.95");
			alp_Location.Insert("Duskar","7841.88 0 8061.18");
			alp_Location.Insert("Fairfield","9978.33 0 6825.94");
			alp_Location.Insert("North Haven","519.69 0 15113.51");
			alp_Location.Insert("Swansisland","1120.0 0 15363.08");
			alp_Location.Insert("Threepwood","9072.89 0 7738.65");
			alp_Location.Insert("KMUC","7226.11 0 11625.59");
			alp_Location.Insert("Baren Fall","7632.45 0 9823.98");
			alp_Location.Insert("Archipelago","2258.34 0 13599.95");
			alp_Location.Insert("Powerplant","4790.48 0 7051.89");
			
		}
	}
	
	
	
	string GetLocation(vector pos)
	{
		float distance = 50000;
		float measure;
		string location = pos.ToString();
		pos[1]=0;
		if (alp_Location.Count() > 0)
		{
			foreach (vector v : alp_Location)
			{
				measure = alpUF.VectorDistance(v,pos);
				if (measure < distance)
				{
					distance = measure;
					location = alp_Location.GetKeyByValue(v);
				
				}
			}
		}		
		return location;
	}

	string GetLocation2(out vector pos)
	{
		float distance = 50000;
		float measure;
		string location = pos.ToString();
		pos[1]=0;
		vector posAdjusted;
		posAdjusted = pos;
		if (alp_Location.Count() > 0)
		{
			foreach (vector v : alp_Location)
			{
				measure = alpUF.VectorDistance(v,pos);
				if (measure < distance)
				{
					distance = measure;
					location = alp_Location.GetKeyByValue(v);
					posAdjusted = v;					
				}
			}
		}		
		pos = posAdjusted;
		return location;
	}
	
}