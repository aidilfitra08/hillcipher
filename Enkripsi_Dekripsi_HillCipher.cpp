#include <iostream>
#include <vector>
using namespace std;

int modInverse(int a, int m)
{
    a = a % m;
    for (int x = -m; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return 0;
}

void getCofactor(vector<vector<int>> &a, vector<vector<int>> &temp, int p, int q, int n)
{
    int i = 0, j = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = a[row][col];
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinant(vector<vector<int>> &a, int n, int N)
{
    int D = 0;
    if (n == 1)
        return a[0][0];
    vector<vector<int>> temp(N, vector<int>(N));
    int sign = 1;
    for (int f = 0; f < n; f++)
    {
        getCofactor(a, temp, 0, f, n);
        D += sign * a[0][f] * determinant(temp, n - 1, N);
        sign = -sign;
    }
    return D;
}

void adjoint(vector<vector<int>> &a, vector<vector<int>> &adj, int N)
{
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }
    int sign = 1;
    vector<vector<int>> temp(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            getCofactor(a, temp, i, j, N);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign) * (determinant(temp, N - 1, N));
        }
    }
}

bool inverse(vector<vector<int>> &a, vector<vector<int>> &inv, int N)
{
    int det = determinant(a, N, N);
    if (det == 0)
    {
        cout << "Inverse does not exist";
        return false;
    }
    int invDet = modInverse(det, 26);
//    cout << det % 26 << ' ' << invDet << '\n';
    vector<vector<int>> adj(N, vector<int>(N));
    adjoint(a, adj, N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inv[i][j] = (adj[i][j] * invDet) % 26;
    return true;
}

int main()
{
mulai:
    string s;
    char loop = 'n';
    int x, y, i, j, k, n;
	
	//inputan plaintext
    cout << "\n==== Program Hill Cipher ====\n\n"
         << "Input (Huruf Kapital): ";
    cin >> s;
    
	//inputan besar matrix
    cout << "Ukuran matriks kunci : ";
    cin >> n;
    cout << "Matriks kunci\n";
    
    //deklarasi variabel matrix
    vector<vector<int>> a(n, vector<int>(n));
    vector<vector<int>> adj(n, vector<int>(n));
    vector<vector<int>> inv(n, vector<int>(n));
    
    //inputan untuk matrix key
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
        	cout<<"Matriks element ("<<i<<","<<j<<") : ";
            cin >> a[i][j];
        }
    }
	//fungsi untuk melakukan inverse key
    if (inverse(a, inv, n))
    {
        cout << '\n';
    };

    int temp = (n - s.size() % n) % n;

    k = 0;
    string ans = "";
    
    //fungsi untuk mencari hasil enkripsi dari plaintext
    while (k < s.size())
    {
        for (i = 0; i < n; i++)
        {
            int sum = 0;
            int temp = k;
            for (j = 0; j < n; j++)
            {
                sum += (a[i][j] % 26 * (s[temp++] - 'A') % 26) % 26;
                sum = sum % 26;
            }
            ans += (sum + 'A');
        }
        k += n;
    }

	//fungsi untuk mencari dekripsi dari hasil ekripsi diatas
    k = 0;
    string deskripsi;
    while (k < ans.size())
    {
        for (i = 0; i < n; i++)
        {
            int sum = 0;
            int temp = k;
            for (j = 0; j < n; j++)
            {
                sum += ((inv[i][j] + 26) % 26 * (ans[temp++] - 'A') % 26) % 26;
                sum = sum % 26;
            }
            deskripsi += (sum + 'A');
        }
        k += n;
    }
    // deskripsi+='\0';
    int f = deskripsi.size() - 1;
    while (deskripsi[f] == 'x')
    {
        f--;
    }
	//output
    cout << "Output : "
         << "\nHasil Enskripsi : " << ans << "\nHasil Deskripsi : " << deskripsi;

    string pilih;
    cout << "\nApakah ingin diulang ? (Y/N) ";
    cin >> pilih;
    
    //fungsi untuk melakukan perulangan program
    if (pilih == "Y" || pilih == "y")
    {
        goto mulai;
    }
    else
    {
        return 0;
    }
}
