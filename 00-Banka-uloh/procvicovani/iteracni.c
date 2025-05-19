
void gausSeidlova(Tmatice* m, int x[], float e)
{
    bool jePresny = false;
    float xOld;
    float suma = 0.0;

    while (!jePresny) {
        jePresny = true; // zacnemem pozitivne
        for (int r = 0; r < m->radku; r++) {
            xOld = x[r];
        
            for (int s = 0; s < m->sloupcu - 1; s++) {
                suma += m->prvek[r][s] * x[s]
            }

            x[r] = m->prvek[r][m->sloupcu - 1 ] - sum

            suma = 0.0;
            jePresny = jePresny && (abs(xOld - x[i]) < eps)
        }
    }

}

























void jacobiho(Tmatice* m, float eps, Tmatice * xpred[])
{
    Tmatice *xnovy = maticeAlokuj(m->radku, 1);
    if(xnovy == NULL) {
        return;
    }
    bool jePresny = false;
    float sum = 0.0;

    while (!jePresny) {
        jePresny = true;

        for (int r = 0; r < m->radku; r++) {
            for (int s = 0; s < m->sloupcu - 1; s++) {
                sum += m->prvek[r][s]*xpred[r];
            }

            xnovy[r] = m->prvek[r][m->sloupcu - 1] - sum;
            sum = 0.0;

            jePresny = jePresny && fabs(x)
        }
    }
}
