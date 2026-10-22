看 * 和 const 的位置：
声明	指针能否改变指向？	能否通过指针修改节点？
node *p	可以	可以
const node *p	可以	不可以
node const *p	可以	不可以
node *const p	不可以	可以
const node *const p	不可以	不可以
可以记住这个规律：
- const node *p：const 修饰 node。
- node *const p：const 修饰指针 p。