package zoo;

public class Ovce extends Zvire {
	public Ovce(String druh, String jmeno, int vek) {
		super(druh, jmeno, vek);
	}

	@Override
	public void zvuk() {
		System.out.println("Bečí: MEEEEEE!");
	}
}
