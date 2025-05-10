package zoo;

// var sez = new ArraysList<String>();
// var cisla = new ArraysList<Integer>();
// List<Integer> cisla = Arrays.asList(1, 2, 4, 3);

import java.util.Arrays;

public class Zoo {

	public static void main(String[] args) {
		Zvire[] zvirata = new Zvire[] {
			new Lev("Lev", "Simba", 5),
			new Slon("Slon", "Dumbo", 10),
			new Ovce("Ovce", "Bela", 3)
		};

		// Seřazení podle jména (pomocí Arrays.sort a Comparator)
		Arrays.sort(zvirata, (z1, z2) -> z1.getJmeno().compareTo(z2.getJmeno()));

		// Výpis pouze zvířat mladších než 6 let
		System.out.println("Zvířata mladší než 6 let:");
		for (Zvire z : zvirata) {
			if (z.getVek() < 6) {
				System.out.println(z.getDruh() + " - " + z.getJmeno() + " (" + z.getVek() + " let)");
			}
		}

		System.out.println("\n--- Kompletní výpis všech zvířat ---");
		vypisZvirata(zvirata);
	}

	public static void vypisZvirata(Zvire[] zvirata) {
		for (Zvire z : zvirata) {
			System.out.println("Druh: " + z.getDruh());
			System.out.println("Jméno: " + z.getJmeno());
			System.out.println("Věk: " + z.getVek());
			System.out.print("Zvuk: ");
			z.zvuk();
			System.out.println("------------------");
		}
	}
}
