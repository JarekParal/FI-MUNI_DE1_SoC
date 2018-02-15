# Jak pracovat s DE1-Soc aneb soupis slepých uliček

## Cíle

1. Zprovoznit na DE1-Soc NIOS II
1. Přeložit a spustit na NIOSu C++ program využívající _cout_, _cin_, _vektory_, ...
1. Nakonfigurovat NIOSu a FPGA periferie
1. Rozběhnout na DE1-Soc (FPGA Cyclone V) linuxový systém
1. Zprovoznit jednoduchou aplikaci, která ovládá periferie připojené přes FPGA k linuxovému systému

## Vývojové prostředí a nástroje

### Tvorba a syntéza HDL
Quartus Prime 16.0 Lite Edition nebo Quartus (Quartus Prime 17.1) Lite Edition

#### Nástroje:
_Qsys_ (Quartus 16.x) a _Platform Designer_ (Qaurtus 17.x) - nástroj pro přidávání IP (Intellectual Properties) do projektu

### Programování NIOSe nebo SOC
Nios II 16.0 Software Build Tools for Eclipse a Nios II Software Build Tools for Eclipse (Quartus Prime 17.1)

## 1. Zprovoznit na DE1-Soc NIOS II

1. Pokus o vytvoření vlastního projektu   
    Při vytváření projektu jsem vesměs postupoval podle videa [Qsys Tutorial 1 - Adder using NIOS II processor](https://www.youtube.com/watch?v=fjIpzcCmZyY) a částečně jsem se i inspiroval [Altera FPGA tutorial - "Hello World" using NIOS II processor on DE1 Board](https://www.youtube.com/watch?v=1a_cD6FBROA).   
    Jen jsem na počátku nevytvářel projekt pomocí výběru čipu (`Device`), ale definoval jsem jej pomocí desky (`Board`): DE1-SoC  
    
    **Problémy:** 
    1. Nelze slinkovat program v Eclipse   
    **Chyba:** `nios '.rwdata' is not within region 'onchip_memory2_0'`  
    Tuto chybu můžete dostat, pokud je program pro NIOS větší než dostupná RAM pamět ([zdroj](http://www.alteraforum.com/forum/showthread.php?t=31187)).  
    **Řešení:** V Qsys je potřeba přenastavit velikost On-chip memory - při vytvoření se nastaví hodnota 4096 bytů - Cyclon 5 V (5CSEMA5F31C6N) zvládne i 400 000 bytů (cca. 80 % _Total block memory bits_) 
    1. Nelze nahrát program do zařízení  
    Vždy, když jsem se dostal do stavu, že jsem mohl nahrát z `Nios II 16.0 Software Build Tools for Eclipse` ukázkový program `Hello world` do FPGA, nepodařilo se mi navázat spojení.  
    **Příčina:** Pravděpodobně špatné sestavení HDL kódu ať už v rámci `Qsys` nebo `Pin Planneru`.  
    **Řešení:** Nenalezeno => Přechod na předpřipravené/ukázkové projekty.

2. Využití ukázkového projektu   
    Pro vývojový kit DE1-SoC je dostupná omezená sada ukázkových projektů (ukázkové CD-ROM), přímo od výrobce kitu Terasic: http://cd-de1-soc.terasic.com   
    Lze v ní nalézt jak ukázky čistě na HDL kód, tak aplikace pro Nios nebo integrovaný ARM procesor.
    Příklady jsou vytvořené ve vývojovém prostředí Quartus Prime 16.0 a při pokusech o zprovoznění na novějších verzích (17.0) jsem občas míval problémy. Proto doporučuji ukázkové projekty zkoušet a upravovat v Quartus Prime 16.x.   
    Pro NIOS jsou k dispozici tyto projekty:   
    * DE1_SoC_ADC: nejjednodušší na úpravy – vhodný jako výchozí program pro další modifikace
    * DE1_SoC_Audio: rozsáhly a dosti složitý projekt – vhodný spíše pro inspiraci
    * DE1_SoC_SDRAM_Nios_Test: relativně jednoduchý projekt, který má již v _Qsys_ nakonfigurovanou SDRAM a kterou lze menší úpravou použít jako RAM pro NIOS procesor  

    Všechny tyto projekty šly bez problémů přeložit jak v Quartus Prime do HDL, tak v Eclipse z C/C++ do programu pro NIOS procesor. Nezaznamenal jsem ani žádné problémy s nahráváním programu do NIOS procesoru (na čemž jsem skončil při vytváření vlastních projektů) a to ani po modifikaci konfigurace FPGA v _Qsys_ nebo úpravě zdrojového kódu v Eclipse.   
    Proto bych toto řešení považoval za funkční a vhodnou cestu při programování NIOS aplikací.

## 2. Přeložit a spustit na NIOSu C++ programy využívající _cout_, _cin_, _vektory_, ...
Po zprovoznění ukázkových NIOS projektů, jsem chtěl rozběhnout i C++ pod NIOSem. V základu v tom není žádný problém. Stačí jen nahradit soubor `main.c` za `main.cpp`. Od toho okamžiku se zdrojový kód začne kompilovat jako C++ a můžete využívat standardní schopnosti jazyka, jako předávání proměnné referencí, defaultní hodnota parametrů funkcí, funkce se stejným jménem ale různými parametry, ale samozřejmě i vytvářet třídy.

Občas může nastat problém s voláním některých funkcí v rámci knihoven dostupných u IP Cores (generovaných přes _Qsys_). S tímto problémech jsem se setkal při využívání knihoven pro PS2 zařízení (myš, klávesnice). Zjistil jsem, že je potřeba přidat do hlavičkových souborů příkaz [`extern "C"`](https://stackoverflow.com/a/12994075).

Větší komplikace nastanou, pokud budete chtít využít možnosti C++ streamů (`cin`, `cout`, `cerr`) nebo [STL (Standard Temlate Library - `vector`, `map`, `set`, ...)](https://en.wikipedia.org/wiki/Standard_Template_Library). Narazíte totiž na problém s nedostatkem RAM pamětí. Při použití těchto funkcionalit dochází k využití velkého množství knihoven a "mašinérie", díky které mohou fungovat streamy a STL, tak jak fungují.

**Řešení:**
1. Zvětšit velikost _On-Chip Memory_   
Možná by šlo realizovat na jiném FPGA, ale na Cyclone V jsem se dostal maximálně na 400 kB (větší velikost již nešla vysyntezovat -> překročení _Total block memory bits_), proto není vhodné řešení pro DE1-Soc
2. Nakonfigurovat NIOS procesor, aby využíval externí 64 MB SDRAM    
Tato RAM je osazenou na DE1-Soc a je použitá i v ukázkovém přikladu *DE1_SoC_SDRAM_Nios_Test*. Zde se ovšem využívá jen pro ukládání uživatelem definovaných dat.   
Pro použití jako hlavní RAM NIOS procesoru, je potřeba překonfigurovat v _Qsys_ NIOS procesor. Konkrétně položku _Vector_ -> _Reset vector memory_ a _Exception vector memory_ z `onchip_memoryXY` na `sdramXY`.   
Následně stačí vygenerovat nový HDL kód. Nechat jej vysentitizovat. Nahrát do FPGA a znovu přeložit program v Eclipse.
Při překladu v Eclipse se nejprve vygeneruje nový _BSP_ (většinou proběhne automaticky, pokud ne, lze vyvolat ručně pomocí `Build All` a nebo v _Project Explorer_ pravým kliknutím na projekt s koncovkou `_bsp`  a následně _NIOS II_ -> _Generate BSP_). BSP vytváří definiční soubory pro C/C++ programy. Následně proběhne standardní překlad programu a již byste měli mít dostatek RAM k používání streamů i STL.

## 3. Nakonfigurovat NIOSu a FPGA periferie

Po zprovoznění NIOSu a C++ za pomoci ukázkových projektů, jsem chtěl rozchodit ovládání některých periferií, obsažených na DE1-Soc. Konkrétně vyzkoušet PS2 konektor (čtení znaků z klávesnice) a VGA výstup (zobrazování výstupu z klávesnice na monitor).

Pro konfiguraci těchto periferií jsem chtěl využít dostupná IP v _Qsys_. Pro PS2 zařízení je k dispozice _PS2 Controller_ a pro VGA výstup _VGA Controller_ + _Character Buffer for VGA Display_.

Ačkoliv jsem se snažil jeden den o zprovoznění _PS2 Controlleru_, nedosáhl jsem funkční verze. Z počátku šlo vše dobře.
Podařilo se mi bez větších problémů přidat _PS2 Controller_ přes _Qsys_ do projektu (v rámci _Qsys_ si lze k jednotlivým IP otevřít dokumentaci). 

Připojil jsem jednotlivé signály:
* Clock Input: pll:outclk0 -> ps2:clk
* Reset: clk50:clk_reset -> ps2:reset
* Avalon Memory Mapped Slave: nios2_gen2:data_master -> ps2:avalon_ps2_slave
* Interrupt Sender: ps2:interrupt_ -> nios2_gen2:irq  

V _Qsys_ vyexportoval: *ps2:external_interface* (stačí poklikat do sloupečku _Export_)

Vygeneroval HDL a vysentitizoval konfiguraci pro FPGA, kterou jsem nahrál do čipu. Otevřel jsem projekt v Eclipse a za pomoci dokumentace k IP jsem sepsal jednoduchý [testovací program](https://github.com/JarekParal/FI-MUNI_DE1_SoC/commit/ad5ece0d2fa4caa8fe547ef310e8c3cc699c5b6c#diff-42cbedc1c3e93cd50a186a2d1bc031f9R43).

Do této chvíle jsem myslel, že je vše v pořádku, ale bohužel nebylo. Nikdy se mi nepodařilo vyčíst [typ PS2 zařízení](https://github.com/JarekParal/FI-MUNI_DE1_SoC/commit/ad5ece0d2fa4caa8fe547ef310e8c3cc699c5b6c#diff-42cbedc1c3e93cd50a186a2d1bc031f9R49) ani jakýkoliv zadaný znak.

Předpokládal jsem problém mezi _Qsys_ komponentou _PS2 Controller_ a mapování fyzických pinů na FPGA. Proto jsem v Quartusu kontroloval pomocí _Pin Planneru_ nepřipojené ale i připojené piny, ale nikde jsem nenarazil na mnou vyexportované piny v Qsys (*ps2:external_interface*). Nevím, jestli se mohli nějak automaticky připojit na piny předdefinované v projektu pro DE1-Soc ale bohužel mi obsluha z NIOSu nefunguje.

Podobná situace nastala i v případě VGA. Kde jsem se dostal do stejného stavu (viz stav v repositáři: https://github.com/JarekParal/FI-MUNI_DE1_SoC - projekt [Nios_Game](https://github.com/JarekParal/FI-MUNI_DE1_SoC/blob/master/DE1_SoC_Nios_Game/software/DE1_SoC_Nios_Game/main.cpp)).

## 4. Rozběhnout na DE1-Soc (FPGA Cyclone V) linuxový systém

Po problémech s NIOSem jsem se rozhodl vyzkoušet vestavěný Soc v FPGA Cyclone V dohromady s linuxovým systémem. Ze stránek http://cd-de1-soc.terasic.com jsem si stáhnul předpřipravené image. 

Lze zde najít čište konzolové verze (_Linux Console_) nebo verze s desktopovým rozhraním (_Linux LXDE Desktop_ a _Linux Ubuntu Desktop_).

Poprvé jsem vyzkoušel desktopovou verzi _Linux LXDE Desktop_ s grafickým rozhraním, kde jsem následně zprovoznil hru naprogramovanou přes SDL v C++. 

Z počátku jsme musel vyřešit problémy s nastavením konfiguračního switche HSEL, kde je potřeba nastavit konfiguraci `000000` pro správné spuštění Linuxu s grafickou nástavbou. Dle popisků na DPS DE1-Soc lze zjistit na které straně je 0 a 1. Většina návodů uvádí konfiguraci jen pro prvních 5 přepínačů, protože poslední šestý je pravděpodobně nevyužit.

Po doinstalování všech potřebných balíčků do systému přes `apt-get` se mi podařilo zkompilovat a spustit jednoduchou hru BomberMan, kterou jsem vytvářel v rámci předmětu PB161.

Bohužel když jsem chtěl zkusit využít i FPGA a ovládat z Linuxu periferie připojené k FPGA (LED, tlačítka, PS2 konektor), zjistil jsem, že to nejde. Pro překonfigurování FPGA z Linuxu je totiž potřeba mít přepínač HSEL ve stavu `010100` (pak je možné nahrávat konfiguraci do FPGA z Linuxu), ale v tento moment nelze spustit Linux s grafickým rozhraním. Popravdě nevím přesně proč.

## 5. Zprovoznit jednoduchou aplikaci, která ovládá periferie připojené přes FPGA k linuxovému systému

Zjistil jsem, že abych mohl konfigurova FPGA z Linuxu musím použit čistě konzolovou verzi (_Linux Console_) a přepínač HSEL ve stavu `010100`. Po tom již lze nahrát přes terminál do FPGA konfiguraci a ovládat jednotlivé periferie jako LED, klávesy, přepínače.

Takto jsem vyzkoušel demonstrační projekt `HPS_LED_HEX` z *DE1-SoC CD-ROM*.

Pro překlad vlastního projektu je potřeba zprovoznit cross-compiling, tak jak je uvedeno v *DE1-SoC User Manual*.

