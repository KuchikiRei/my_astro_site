// @ts-check
import { defineConfig } from 'astro/config';

// https://astro.build/config
export default defineConfig({
    // 1. 设置为你未来的 GitHub Pages 完整网址
    // 请把 <你的GitHub用户名> 替换成你真实的用户名
    site: 'https://KuchikiRei.github.io',
    
    // 2. 设置为你的 GitHub 仓库名称（前面必须带斜杠 /）
    // 请把 <你的仓库名称> 替换成你刚刚在 GitHub 上建的仓库名
    base: '/my_astro_site',
});