##  1. **Ước số & phân tích thừa số**

Cho ( n = \displaystyle\prod_{i=1}^k p_i^{e_i} ) là phân tích thừa số nguyên tố.

* 📌 **Số ước** (d(n)):
  [
  d(n) = \prod_{i=1}^k (e_i + 1)
  ]

* 📌 **Tổng các ước** (σ(n)):
  [
  \sigma(n) = \prod_{i=1}^k \frac{p_i^{e_i+1}-1}{p_i-1}
  ]

* 📌 **Hàm Ω** (tổng số thừa số kể cả lặp):
  [
  \Omega(n) = \sum_{i=1}^k e_i
  ]

* 📌 **Hàm ω** (số lượng thừa số nguyên tố khác nhau):
  [
  \omega(n) = k
  ]

* 📌 **Bất đẳng thức cơ bản**:
  (\displaystyle \Omega(n) \le \lfloor \log_2 n \rfloor)
  đạt cực đại khi (n = 2^a).


👉 Nếu bạn muốn, tôi có thể biên soạn những công thức này thành **1 “cheat sheet” ngắn gọn PDF** để bạn dùng khi luyện thi ICPC/Codeforces. Bạn có muốn tôi tạo file đó không? 📄✨
