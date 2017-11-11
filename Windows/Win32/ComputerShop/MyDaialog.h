#define IDCPU				110
#define IDCPU1				111
#define IDCPU2				112
#define IDCPU3				113
#define ID_ETCPU			114

#define IDRAM				115
#define IDRAM1				116
#define ID_ETRAM			117

#define IDMOTHERBOARD		120
#define IDMOTHERBOARD1		121
#define ID_ETMOTHERBOARD	122

#define IDGRAPHIC			125
#define IDGRAPHIC1			126
#define IDGRAPHIC2			127
#define ID_ETGRAPHIC		128

#define IDHARD				130
#define IDHARD1				131
#define ID_ETHARD			132

#define IDCD				135
#define IDCD1				136
#define ID_ETCD				137

#define IDSMPS				140
#define ID_ETSMPS			141

#define	IDCABINATE			145
#define	IDCABINATE1			146
#define ID_ETCABINATE		147

#define IDKEYBOARD			150
#define IDKEYBOARD1			151
#define ID_ETKEYBOARD		152

#define IDMOUSE				155
#define IDMOUSE1			156
#define ID_ETMOUSE			157

#define	IDMONITOR			160
#define IDMONITOR1			161
#define IDMONITOR2			162
#define ID_ETMONITOR		163

#define IDPRINTER			165
#define ID_ETPRINTER		166

#define ID_PBCONTINUE		100

struct STATIC_TEXT
{
	TCHAR HEADINGD[9][50] = { TEXT("DEVICE"),TEXT("COMPANY"),TEXT("SUB-TYPE"),TEXT("GENRATION"),TEXT("SIZE"),TEXT("MODEL"),TEXT("INCES"),TEXT("PRICE") ,TEXT("TOTAL") };
	TCHAR DEVICES[12][60] = { TEXT("CPU	"),TEXT("RAM "),TEXT("Motherboard"),TEXT("Graphics Card"),TEXT("Hard Disks"),TEXT("CD/DVD Drive"),TEXT("SMPS"),TEXT("Cabinet"),TEXT("Keyboard"),TEXT("Mouse"),TEXT("Monitor"),TEXT("Printer") };
	TCHAR MESSAGES[2][100] = {TEXT("Press 'P' to print the reciept and if you want to Close program press 'ESC'"),TEXT("Thanks for shoping please do visit us again press 'ESC'")};
}st;

struct SELECTED_ITEM
{
	TCHAR CPU[4][50];
	TCHAR RAM[2][50];
	TCHAR MOTHERBOARD[2][50];
	TCHAR GRAPHIC[3][50];
	TCHAR HARD[2][50];
	TCHAR CDDVD[2][50];
	TCHAR SMPS[1][50];
	TCHAR CABINATE[2][50];
	TCHAR KEYBOARD[2][50];
	TCHAR MOUSE[2][50];
	TCHAR MONITOR[3][50];
	TCHAR PRINTER[1][50];
	int Total;
	TCHAR TOTAL_PRICE[10];
}si;

struct CPU
{
	TCHAR Company[3][50] = { TEXT("-----SELECT------"),TEXT("INTEL                    "),TEXT("AMD                        ") };

	TCHAR SubtypeA[3][50] = { TEXT("i3 Genration             "),TEXT("i5 Genration             "),TEXT("i7 Genration             ") };
	int SubtypeAPrice[3] = { 110,120,130 };
	TCHAR SubtypeB[3][50] = { TEXT("A                        "),TEXT("B                        "),TEXT("C                        ") };
	int SubtypeBPrice[3] = { 210,220,230 };

	TCHAR GenrationA[3][50] = { TEXT("i3-A                     "),TEXT("i5-A                     "),TEXT("i7-A                     ") };
	int GenrationAPrice[3] = { 110,120,130 };
	TCHAR GenrationB[3][50] = { TEXT("i3-B                     "),TEXT("i5-B                     "),TEXT("i7-B                     ") };
	int GenrationBPrice[3] = { 210,220,230 };

	TCHAR ModelA[3][50] = { TEXT("i3-A-A                   "),TEXT("i5-A-A                   "),TEXT("i7-A-A                   ") };
	int ModelAPrice[3] = { 110,120,130 };
	TCHAR ModelB[3][50] = { TEXT("i3-B-B                   "),TEXT("i5-B-B                   "),TEXT("i7-B-B                   ") };
	int ModelBPrice[3] = { 210,220,230 };

	int Price = 0;
	TCHAR CPU_PRICE[5];
}cb;

struct RAM
{
	TCHAR Company[5][50] = { TEXT("-----SELECT------") , TEXT("Cosair                   "), TEXT("G.Skill                  ") ,TEXT("OCZ                     ") ,TEXT("Muskin                   ")};
	
	TCHAR SizeA[3][50] = { TEXT("4 GB                     "),TEXT("8 GB                     "),TEXT("16 GB                     ") };
	int SizeAPrice[3] = { 10,20,30 };

	TCHAR SizeB[3][50] = { TEXT("4 GB                     "),TEXT("8 GB                     "),TEXT("16 GB                    ") };
	int SizeBPrice[3] = { 110,120,130 };

	TCHAR SizeC[3][50] = { TEXT("4 GB                     "),TEXT("8 GB                     "),TEXT("16 GB                    ") };
	int SizeCPrice[3] = { 210,220,230 };

	TCHAR SizeD[3][50] = { TEXT("4 GB                     "),TEXT("8 GB                     "),TEXT("16 GB                    ") };
	int SizeDPrice[3] = { 310,320,330 };

	int Price = 0;
	TCHAR RAM_PRICE[5];
}ram;

struct  MOTHERBOARD
{
	TCHAR Company[5][50] = { TEXT("-----SELECT------") ,TEXT("Asus                     ") ,TEXT("Gigabyte                 "),TEXT("Biostar                  "),TEXT("AsRock                   ")};

	TCHAR TypeA[3][50] = {TEXT("Prime H270-Plus          ") , TEXT("Asus Intel H61M-CS       ") ,TEXT("Asus H81M-CS             ")};
	int TypeAPrice[3] = {10,20,30};

	TCHAR TypeB[3][50] = { TEXT("Gigabyte GA-H110M-S2     ") ,TEXT("Gigabyte GA-H61M-S       ") ,TEXT("Gigabyte GA-B250-DS3H    ") };
	int TypeBPrice[3] = { 110,120,130 };

	TCHAR TypeC[3][50] = { TEXT("Biostar H81MHV3          ") ,TEXT("Biostar B150GT5          ") ,TEXT("Biostar A68N-2100        ") };
	int TypeCPrice[3] = { 210,220,230 };

	TCHAR TypeD[3][50] = { TEXT("Asrock B250M Pro4        ") ,TEXT("Asrock AB350             ") ,TEXT("Asrock AB345              ") };
	int TypeDPrice[3] = { 310,320,330 };

	int Price = 0;
	TCHAR MOTHERBOARD_PRICE[5];
}motherboard;

struct GRAPHIC
{
	TCHAR Company[4][50] = { TEXT("-----SELECT------") ,TEXT("NVIDIA                   ") ,TEXT("AMD                      ") ,TEXT("ZOTAC                    ") };
	
	TCHAR TypeA[4][50] = { TEXT("GeForce GTX 1050         ") ,TEXT("GeForce GTX 1060         ") ,TEXT("GeForce GTX 1080         ") ,TEXT("GeForce GTX 1080 Ti      ") };
	int TypeAPrice[3] = { 10,20,30 };

	TCHAR TypeB[3][50] = { TEXT("AMD Radeon R7 240        ") ,TEXT("AMD Radeon R9 280X       ") ,TEXT("AMD Radeon Pro Duo       ") };
	int TypeBPrice[3] = { 110,120,130 };

	TCHAR TypeC[3][50] = { TEXT("Zotac NVIDIA GT 730      ") ,TEXT("Zotac NVIDIA GT 1050 Ti  ") ,TEXT("Zotac NVIDIA GT 1050     ")};
	int TypeCPrice[3] = { 210,220,330 };

	TCHAR CardSize[3][50] = { TEXT("2GB                      ") ,TEXT("4GB                      "),TEXT("8GB                      ")};
	int CardSizePrice[3] = { 310,320,330 };

	int Price = 0;
	TCHAR GRAPHIC_PRICE[5];

}graphic;

struct HARDDISK
{
	TCHAR Company[3][50] = { TEXT("-----SELECT------") ,TEXT("Western Digital          ") ,TEXT(" Seagate                 ") };
	
	TCHAR HardDiskSize[3][50] = { TEXT("500GB                    ") ,TEXT("1TB                      ") ,TEXT("2TB                      ") };

	int WesternDigitalPrice[3] = { 10,20,30};
	int SeagatePrice[3] = { 110,120,130 };

	int Price = 0;
	TCHAR HARDDISK_PRICE[5];

}harddisk;

struct CDDVD
{
	TCHAR Company[4][50] = { TEXT("-----SELECT------") ,TEXT("AMW                      ") ,TEXT("Astrad                   ") ,TEXT("Acrox                    ") };

	TCHAR TypeA[4][50] = {TEXT("AMW S99 DVD Player       ") ,TEXT("AmphionAMW V99 Player    ") ,TEXT("AMW M280 Portable        ") ,TEXT("AMW DVD Player V99       ")};
	int TypeAPrice[4] = {10,20 ,30,40};

	TCHAR TypeB[4][50] = {TEXT("Astrad S99 DVD Player    ") ,TEXT("AmphionAstrad V99 Player ") ,TEXT("Astrad M280 Portable     ") ,TEXT("Astrad DVD Player V99    ") };
	int TypeBPrice[4] = { 110,120 ,130,140 };

	TCHAR TypeC[4][50] = {TEXT("Acrox S99 DVD Player     ") ,TEXT("AmphionAcrox V99 Player  ") ,TEXT("Acrox M280 Portable      ") ,TEXT("Acrox DVD Player  V99    ") };
	int TypeCPrice[4] = { 210,220 ,230,240 };

	int Price = 0;
	TCHAR CDDVD_PRICE[5];

}cddvd;

struct SMPS
{
	TCHAR Company[3][50] = { TEXT("-----SELECT------") , TEXT("Siemens        "),TEXT("Misutbhishi    ") };
	int CompanyPrice[2] = { 1500,1000 };

	int Price = 0;
	TCHAR SMPS_PRICE[5];
}smps;

struct CABINATE
{
	TCHAR Company[4][50] = { TEXT("-----SELECT------") ,TEXT("Circle                   ") ,TEXT("Antec                    ") ,TEXT("Corsair                  ") };

	TCHAR TypeA[3][50] = { TEXT("Circle Pheonix Cabinet   ") ,TEXT("Circle CC819             ") ,TEXT("Circle CC 890            ") };
	int TypeAPrice[3] = { 5000,6000,5500 };

	TCHAR TypeB[3][50] = { TEXT("Corsair Carbide 2100     ") ,TEXT("Corsair Carbide 123      ") ,TEXT("Corsair Carbide 900      ") };
	int TypeBPrice[3] = { 5000,4500,4000 };

	TCHAR TypeC[3][50] = { TEXT("Antec Cabinet gx200      ") ,TEXT("Antec Cabinet x1         ") ,TEXT("Antec Cabinet 900        ") };
	int TypeCPrice[3] = { 5000,4000,6000 };

	int Price = 0;
	TCHAR CABINATE_PRICE[5];

}cabinate;

struct KEYBOARD
{
	TCHAR Company[4][50] = { TEXT("-----SELECT------") ,TEXT("Yamaha                   ") ,TEXT("KORG                    ") ,TEXT("Roland                   ") };

	TCHAR KeyboardType[2][50] = { TEXT("Wired                    ") ,TEXT("Wireless                 ") };

	int TypeAPrice[3] = { 10,20 };

	int TypeBPrice[3] = { 110,120 };

	int TypeCPrice[3] = { 210,220 };

	int Price = 0;
	TCHAR KEYBOARD_PRICE[5];
}keyboard;

struct MOUSE
{
	TCHAR Company[4][50] = { TEXT("-----SELECT------") ,TEXT("Logitech                 ") ,TEXT("Asus                     ") ,TEXT("Corsair                  ") };

	TCHAR MouseType[2][50] = { TEXT("Wired                    ") ,TEXT("Wireless                 ") };

	int TypeAPrice[2] = { 500,700 };
	int TypeBPrice[2] = { 700,900 };
	int TypeCPrice[2] = { 500,800 };

	int Price = 0;
	TCHAR MOUSE_PRICE[5];
}mouse;

struct MONITOR
{
	TCHAR Company[4][50] = { TEXT("-----SELECT------"),TEXT("Sony                     ") ,TEXT("HP                       ") ,TEXT("DELL                     ") };

	TCHAR TypeA[3][50] = { TEXT("Sony Bravia              ") ,TEXT("Sony XAV                 ") ,TEXT("Sony XLM                 ") };
	int TypeAPrice[3] = { 10,20,30 };

	TCHAR TypeB[3][50] = { TEXT("HP Bravia                ") ,TEXT("HP XAV                   ") ,TEXT("HP XLM                   ") };
	int TypeBPrice[3] = { 110,120,130 };

	TCHAR TypeC[3][50] = { TEXT("Dell MSD14               ") ,TEXT("Dell 12216HV             ") ,TEXT("Dell SE2216H             ") };
	int TypeCPrice[3] = { 210,220,230 };

	TCHAR MoitorSize[3][50] = { TEXT("18 inches                "),TEXT("21 inches                "),TEXT("24 inches                ") };
	int MoitorSizePrice[3] = {310,320,330};

	int Price = 0;
	TCHAR MONITOR_PRICE[5];

}monitor;

struct PRINTER
{
	TCHAR Company[3][50] = { TEXT("-----SELECT------") ,TEXT("HP             "),TEXT("IBM            ")};
	int CompanyPrice[2] = { 1500,2000 };

	int Price = 0;
	TCHAR PRINTER_PRICE[5];
}printer;
