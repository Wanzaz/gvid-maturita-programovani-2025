public class Zoo {

	public static void main(String[] args) {
		String[] druhy = {"Lev", "Slon", "Ovce"};
		String[] jmena = {"Simba", "Dumbo", "Bela"};
		int[] veky = {5, 10, 3};

		for (int i = 0; i < druhy.length; i++) {
			System.out.println("Druh: " + druhy[i]);
			System.out.println("Jméno: " + jmena[i]);
			System.out.println("Věk: " + veky[i]);

			System.out.print("Zvuk: ");
			if (druhy[i].equals("Lev")) {
				System.out.println("AAAAAA");
			} else if (druhy[i].equals("Slon")) {
				System.out.println("PFFFFFF");
			} else if (druhy[i].equals("Ovce")) {
				System.out.println("MEEEEEE");
			}

			System.out.println("------------------");
		}
	}
}

