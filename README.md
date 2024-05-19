# KOShooter

Projekt zaliczeniowy na SGD (Symulacje i gry decyzyjne) na Polsko-Japońskiej Akademii Technik Komputerowych w Gdańsku.

## Opis gry

Gra jest typowym space shooterem. Celem jest zebranie jak największej ilości punktów, które wypadają w postaci kul z zabitych przeciwników.
Gracz jest w stanie wytrzymać 5 trafień. Przeciwnicy wytrzymują od 1 do 3 trafień.

## Wzorce

- main.cpp inicjalizuje konstruktor klasy App, który tworzy instancje menedżera dźwięku (`SoundManager`), tekstu (`TextManager`), klawiatury (`InputHandler`), renderera (`Renderer`) oraz całej "sceny" gry (`Stage`) wraz z logiką gry.
- ilość klatek na sekundę wynosi 60, za "wstrzymywanie" aplikacji odpowiada metoda `capFrameRate` w klasie App
- gracz, przeciwnicy, punkty, eksplozje oraz szczątki są instancjami ogólnej klasy `Entity`.
- klasa `Stage` odpowiada za zarządzanie całą logiką gry.
  - gracz, przeciwnicy, punkty, eksplozje oraz szczątki zarządzane są przy pomocy list połączonych (_linked list_). Lista zawiera instancje klasy `Entity`.
  - listy posiadają `Head` oraz wskaźnik na `Tail` (instancje klasy `Entity`)
  - podczas iteracji gry, iterowane są wszystkie listy i dochodzi do update'u stanów poszczególnych instancji klasy `Entity`
  - jeśli, np. przeciwnik zostaje zabity, dochodzi do aktualizacji wskaźnika `next` na poprzednim elemencie w liście. Potem następuje usunięcie elementu. Jeśli element jest ostatni w liście to dochodzi do aktualizacji wskaźnika `Tail`.

## Elementy fizyki

- Grawitacja jest wykorzystywana w szczątkach (Debris), które powstają po zniszczeniu przeciwników (`d->dy += 0.5;`).
- Kolizje kul z przeciwnikami oraz gracza z punktami. Statyczna metoda kolizji znajduje się w klasie `Util::collision`.

## Źródło

Bazowałem na tutorialu [Pararell Realities](https://www.parallelrealities.co.uk/tutorials/shooter/shooter1.php). W oryginale gra została wykonana w C, natomiast postanowiłem ją przepisać na C++ i wykorzystać klasy do zarządzania stanami gry.

## Autor

Łukasz Kos, s22051
