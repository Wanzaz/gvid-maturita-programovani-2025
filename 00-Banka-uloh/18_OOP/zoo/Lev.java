package zoo;

public class Lev extends Zvire {
	public Lev(String druh, String jmeno, int vek) {
		super(druh, jmeno, vek);
	}

	@Override
	public void zvuk() {
		System.out.println("Řve hlasitě: AAAAAAAA!");
	}
}

