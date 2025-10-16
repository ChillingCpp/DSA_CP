Cho n=∏i=1kpiein = \displaystyle\prod_{i=1}^k p_i^{e_i}n=i=1∏k​piei​​ là phân tích thừa số nguyên tố.

- 📌 **Số ước** (d(n)):
    
    d(n)=∏i=1k(ei+1)d(n) = \prod_{i=1}^k (e_i + 1)d(n)=i=1∏k​(ei​+1)
- 📌 **Tổng các ước** (σ(n)):
    
    σ(n)=∏i=1kpiei+1−1pi−1\sigma(n) = \prod_{i=1}^k \frac{p_i^{e_i+1}-1}{p_i-1}σ(n)=i=1∏k​pi​−1piei​+1​−1​
- 📌 **Hàm Ω** (tổng số thừa số kể cả lặp):
    
    Ω(n)=∑i=1kei\Omega(n) = \sum_{i=1}^k e_iΩ(n)=i=1∑k​ei​
- 📌 **Hàm ω** (số lượng thừa số nguyên tố khác nhau):
    
    ω(n)=k\omega(n) = kω(n)=k
- 📌 **Bất đẳng thức cơ bản**:  
    Ω(n)≤⌊log⁡2n⌋\displaystyle \Omega(n) \le \lfloor \log_2 n \rfloorΩ(n)≤⌊log2​n⌋  
    đạt cực đại khi n=2an = 2^an=2a.
    
✅ Ứng dụng:
- Đếm số ước (phổ biến trong bài toán “divisor counting”)
- Tối ưu chọn số có nhiều thừa số nhất
- Phân tích nhanh độ dài chuỗi chia thừa số
