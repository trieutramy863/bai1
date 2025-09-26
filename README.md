# bai1
bai1
# 1. Caesar cipher (Mã Caesar)
# Tên gọi

Caesar cipher (dịch Caesar) — dịch vòng các chữ cái theo một độ dịch t.

# Thuật toán

Bản mã hoá (encrypt): với mỗi ký tự chữ hoa/thuong x, chuyển thành (x + t) mod 26 (t ∈ {0..25}).

Giải mã (decrypt): (x - t + 26) mod 26.

Pseudocode (với chỉ chữ cái A–Z):
# Không gian khoá

|K| = 26 (t = 0..25). Rất nhỏ.

# Cách phá (không cần khoá)

Brute-force: thử 26 giá trị t; đọc hoặc kiểm tra bằng tần suất/ngôn ngữ.

Frequency analysis: đối với văn bản đủ dài, chữ có tần suất cao nhất (ví dụ 'E') ánh xạ tới một chữ cái → suy ra t.

# C++ (đơn giản)
# <img width="1920" height="1200" alt="Screenshot 2025-09-26 124611" src="https://github.com/user-attachments/assets/18827b18-4421-44e9-b853-cd13f97e1dd9" />
# HTML+CSS+JS (giao diện nhỏ)
# <img width="584" height="341" alt="image" src="https://github.com/user-attachments/assets/3ddfe242-e5d1-48ba-b1c1-08fe82c9bbda" />
# 2. Affine cipher (Mã Affine)
# Tên gọi

Affine cipher — biến đổi tuyến tính trên tập các chữ cái mod m: E(x) = (a*x + b) mod m.

# Thuật toán

Mã hoá: với chữ cái số x (A=0..Z=25), khoá là (a,b) với gcd(a,26)=1:

y = (a*x + b) mod 26


Giải mã: cần a_inv (nghịch đảo modulo 26), x = a_inv * (y - b) mod 26.
a phải là nguyên tố tới 26 (coprime) → có 12 giá trị khả dĩ (1,3,5,7,9,11,15,17,19,21,23,25).

Không gian khoá

Số khóa = φ(26) * 26 = 12 * 26 = 312.

# Cách phá (không cần khoá)

Brute-force: thử 312 cặp (a,b) và chọn bản rõ có ý nghĩa (tự động hoặc bằng mắt).

Frequency analysis: dùng tương tự Caesar nhưng vì có a, cần thử các a có thể và đối chiếu tần suất.

Known plaintext: dễ suy a và b nếu biết một cặp plaintext–ciphertext.

# C++ (encrypt/decrypt)
# <img width="960" height="600" alt="image" src="https://github.com/user-attachments/assets/dd0d74af-231e-44e1-a584-6e7a93062ff7" />
# HTML+JS (giao diện)
# <img width="1145" height="532" alt="Screenshot 2025-09-25 224032" src="https://github.com/user-attachments/assets/4a852f37-48ea-4dbb-8a5b-eaea55a0c85f" />
# 3. Permutation cipher (Transposition / Hoán vị)
Ở đây mình hiểu là Columnar transposition (hoán vị cột) — hay chung chung: tách văn bản thành block rồi hoán vị vị trí ký tự theo một permutaion.
# Tên gọi
Permutation cipher / transposition cipher / Columnar transposition (mã hoán vị).
# Thuật toán (columnar transposition tiêu biểu)
Chọn độ dài key = n; key là một hoán vị các cột (ví dụ 4 1 3 2).

Viết plaintext theo hàng vào ma trận với n cột (bổ sung ký tự padding nếu cần).

Đọc cột theo thứ tự của hoán vị để tạo ciphertext.

Ví dụ: key order [3,1,2] (nghĩa: đọc cột 3 trước, sau đó 1,2).

# Giải mã

Biết n và hoán vị, ta biết số hàng = ceil(len(text)/n). Xây ma trận và điền ciphertext vào cột theo thứ tự hoán vị rồi đọc theo hàng.

Không gian khoá

Số khoá = n! (với cột n). Nếu n lớn thì rất lớn: n! tăng rất nhanh (ví dụ 10! = 3,628,800).

Cách phá (không cần khoá)

Phân tích độ dài cột: thử các n khả dĩ (thử số cột từ 2 tới, ví dụ, 20), chuyển mã ngược cho từng hoán vị (n! lớn) — nhưng ta có thể dùng heuristics:

Kí tự/digram frequency khi đoán cấu trúc cột.

Hill-climbing / simulated annealing: tối ưu hóa điểm số ngôn ngữ (log-likelihood, n-gram scoring).

Known-plaintext: nếu biết mẩu plaintext, dễ suy key.

Đo lường “engram”: thử các n và sắp xếp cột sao cho bigram/trigram có độ khả dĩ cao khi đọc hàng.
# C++ (columnar transposition - encrypt/decrypt)
# <img width="960" height="600" alt="image" src="https://github.com/user-attachments/assets/0ed5abd9-acbb-4fc6-b5c7-c034abbba207" />
# HTML+JS (đơn giản) 
# <img width="583" height="270" alt="image" src="https://github.com/user-attachments/assets/2015f077-1a11-4467-ac65-8b026fb440f3" />
# 4. Vigenère cipher
# Tên gọi

Vigenère cipher — mã hoá theo khóa lặp, từng ký tự được dịch bởi Caesar khác nhau theo chữ khóa.

# Thuật toán

Mã hoá: key K = k0 k1 ... k_{m-1} (m = độ dài khóa), chuyển each plaintext letter P[i] → C[i] = (P[i] + K[i mod m]) mod 26 (với K[...] là số 0..25 tương ứng chữ).

Giải mã: P[i] = (C[i] - K[i mod m] + 26) mod 26.

# Không gian khoá

Nếu khóa độ dài m thì |K| = 26^m. Nếu m không biết, tổng không gian là sum_{m<=M} 26^m lớn rất nhanh.

# Cách phá (không cần khoá)

Kasiski examination: tìm các khoảng cách giữa các lặp của đoạn chữ (trigram, v.v.) trong ciphertext → Ước lượng độ dài khóa m (những ước chung của khoảng cách).

Friedman test (Index of Coincidence): ước lượng m bằng IC.

Sau khi biết m (hoặc ước lượng), chia ciphertext thành m dãy (các chữ ở vị trí i mod m) — mỗi dãy là một Caesar cipher → áp dụng frequency analysis cho từng dãy để tìm shift tương ứng (chiến lược: assume 'E' maps to most frequent, hoặc dùng correlation với bảng tần suất).

Brute-force: nếu m nhỏ, thử 26^m.

Modern heuristic: hill-climbing với score ngôn ngữ.

# C++ (encrypt/decrypt)
# <img width="960" height="600" alt="image" src="https://github.com/user-attachments/assets/9a1a1ee4-88ab-4857-83af-18e3e65d4fc8" />
# HTML+JS
# <img width="581" height="242" alt="image" src="https://github.com/user-attachments/assets/5a5e3f9e-914b-44bc-81a8-c4810a116bea" />
# 5. Playfair cipher
# Tên gọi

Playfair cipher — mã hoán vị chữ đôi (digraph) dùng bảng chữ 5×5 (kết hợp I/J thường) do Charles Wheatstone nhưng phổ biến bởi Playfair.

# Luật & Thuật toán

Tạo bảng 5×5: sử dụng từ khoá (loại bỏ chữ trùng, kết hợp I/J) rồi điền các chữ cái còn lại. Ví dụ keyword "MONARCHY".

Tiền xử lý plaintext:

Loại ký tự không phải chữ, viết hoa, thay J → I (hoặc ngược lại tùy quy ước).

Chia plaintext thành các cặp (digraphs). Nếu một cặp có hai chữ giống nhau, chèn X (hoặc Q) giữa để phân tách. Nếu dư 1 chữ cuối, thêm X padding.

Mã hoá mỗi digraph (A,B):

Nếu A và B cùng hàng → thay bằng ký tự bên phải của mỗi chữ (vòng lại).

Nếu cùng cột → thay bằng ký tự bên dưới của mỗi chữ (vòng lại).

Nếu khác hàng & cột → thay mỗi chữ bằng chữ ở cùng hàng nhưng ở cột của chữ kia (như tạo rectangle).

Giải mã: tương tự nhưng đảo hướng (trái / trên).

# Không gian khoá

Mỗi khoá tương đương với một sắp xếp của 25 chữ cái → khoảng 25! ≈ 1.55×10^25 khả năng. (Rất lớn; thực tế từ khóa thường là một từ -> không gian nhỏ hơn.)

Cách phá (không cần khoá)

Frequency analysis on digraphs: Playfair mã hóa theo digraph → tần suất bigram quan trọng.

Hill-climbing / simulated annealing: tối ưu mô hình ngôn ngữ (score từ bảng bigram/trigram) — phương pháp hiện đại hiệu quả.

Known plaintext/crib: nếu biết một phần văn bản sẽ giúp suy ma trận.

Brute-force: không khả thi nếu không giới hạn kiểu khoá.

# C++ (Playfair basic)
# <img width="960" height="600" alt="image" src="https://github.com/user-attachments/assets/710c4589-5ee3-40fa-b5f3-04ceda3adba5" />
# HTML+JS (Playfair)
# <img width="677" height="296" alt="image" src="https://github.com/user-attachments/assets/81ebd6f4-da66-4377-b039-095b0dae57ef" />

