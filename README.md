# Hra na FPGA Cyclone V

## Cíl

Naprogramovat jednoduchou hru na FPGA Cyclone V (vývojová deska DE1-Soc) za pomocí softwarově definovaného procesoru NiosII. Hra má být ovládána pomocí PS2 klávesnice a grafický výstup má být zobrazen přes VGA rozhraní.

### Osobní cíle

- poznat Qsys a NiosII
- pokusit se zprovoznit C++ pod NiosII
- naprogramovat hru v C++

## Vývojové prostředí

Quartus Prime 16.0 Lite Edition a Quartus (Quartus Prime 17.1) Lite Edition + Nios II 16.0 Software Build Tools for Eclipse

## Vytvoření projektu

1. **Pokus o vytvoření vlastního projektu**  
Při vytváření projektu jsem vesměs postupoval podle videa [Qsys Tutorial 1 - Adder using NIOS II processor](https://www.youtube.com/watch?v=fjIpzcCmZyY) a částečně jsem se i inspiroval [Altera FPGA tutorial - "Hello World" using NIOS II processor on DE1 Board](https://www.youtube.com/watch?v=1a_cD6FBROA).   
Jen jsem na počátku nevytvářal projekt pomocí výběru čipu (`Device`), ale definoval jsem jej pomocí desky (`Board`): DE1-SoC  
**Problémy:** 
    1. Nelze slinkovat program v Eclipse   
    **Chyba:** `nios '.rwdata' is not within region 'onchip_memory2_0'`  
    Tuto chybu můžete dostat, pokud je program pro NIOS větší než dostupná RAM pamět ([zdroj](http://www.alteraforum.com/forum/showthread.php?t=31187)).  
    **Řešení:** V Qsys je potřeba přenastavit velikost On-chip memory - při vytvoření se nastaví hodnota 4096 bytů - Cyclon 5 V (5CSEMA5F31C6N) zvládne i 400 000 bytů (cca. 80 % Total block memory bits) 
    1. Nelze nahrát program do zařízení  
    Vždy, když jsem se dostal dostal do stavu, že jsem mohl nahrát z `Nios II 16.0 Software Build Tools for Eclipse` ukázkový program `Hello world` do FPGA, nepodařilo se mi navázat spojení.  
    **Příčina**: Pravděpodobně špatné sestavení HDL kódu ať už v rámci `Qsys` nebo `Pin Planneru`.  
    **Řešení**: Nanelezeno => Přechod na předpřipravené projekty.

2. Využití ukázkového projektu   
Pro vývojový kit DE1-SoC je dostupná omezená sada ukázkových projektů (ukázkové CD-ROM), přímo od výrobce kitu Terasic: http://cd-de1-soc.terasic.com   
Lze v ní nalézt jak ukázky číště na HDL kód, tak aplikace pro Nios nebo integrovaný ARM procesor.
Příklady jsou vytvořené ve vývojovém prostředí Quartus Prime 16.0 a při pokusech o zprovoznění na novějších verzích (17.0) jsem měl vždy nějaké problémy. Proto doporučuji  