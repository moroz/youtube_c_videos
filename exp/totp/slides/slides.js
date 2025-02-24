import dayjs from "https://esm.sh/dayjs@latest";

async function loadSlides() {
  const promises = [];

  document.querySelectorAll("section[data-src]").forEach((section) => {
    promises.push(
      new Promise(async (resolve) => {
        const res = await fetch(section.dataset.src);
        const html = await res.text();
        const dom = new DOMParser().parseFromString(html, "text/html");
        const wrapper = document.createElement("div");
        wrapper.innerHTML = dom.querySelector("section").innerHTML;
        section.appendChild(wrapper);
        resolve();
      }),
    );
  });

  return await Promise.all(promises);
}

class PPTController {
  sections = [];
  activeIndex = 0;

  constructor() {
    loadSlides()
      .then(this.detectSections)
      .then(this.setupKeyHandlers)
      .then(() => this.setSlide(0))
      .then(() => this.setupUnixCounters());
  }

  detectSections = () => {
    this.sections = document.querySelectorAll("body > section");
  };

  setSlide = (i) => {
    document
      .querySelectorAll("section.visible")
      .forEach((s) => s.classList.remove("visible"));
    this.sections[i]?.classList.add("visible");
  };

  nextSlide = () => {
    if (this.activeIndex >= this.sections.length - 1) {
      return;
    }

    this.activeIndex++;
    this.setSlide(this.activeIndex);
  };

  previousSlide = () => {
    if (this.activeIndex <= 0) {
      return;
    }

    this.activeIndex--;
    this.setSlide(this.activeIndex);
  };

  setupKeyHandlers = () => {
    window.addEventListener("keydown", (e) => {
      switch (e.key) {
        case "ArrowDown":
        case "ArrowRight":
        case "PageDown":
        case " ":
          e.preventDefault();
          this.nextSlide();
          break;

        case "ArrowUp":
        case "ArrowLeft":
        case "PageUp":
          e.preventDefault();
          this.previousSlide();
          break;
      }
    });
  };

  setupUnixCounters() {
    const unixContainers = [...document.querySelectorAll("[data-unix]")];
    const stepContainers = [...document.querySelectorAll("[data-step]")];
    const timeContainers = [...document.querySelectorAll("[data-time]")];
    const stepHexContainers = [...document.querySelectorAll("[data-step-hex]")];

    setInterval(() => {
      const now = new Date();
      const unixepoch = Math.floor(Number(now) / 1000);
      const t = Math.floor(unixepoch / 30);
      for (const unix of unixContainers) {
        unix.textContent = String(unixepoch);
      }
      for (const t of timeContainers) {
        t.textContent = dayjs(now).format("YYYY-MM-DD HH:mm:ss");
      }
      for (const step of stepContainers) {
        step.textContent = String(t);
      }
      const buf = new ArrayBuffer(8);
      const view = new DataView(buf);
      view.setUint32(4, t, false);
      const bytes = Array.from(new Uint8Array(buf));

      for (const hex of stepHexContainers) {
        const cells = [...hex.querySelectorAll("td")];
        for (let i = 0; i < 8; i++) {
          cells[i].textContent = bytes[i].toString(16).padStart(2, "0");
        }
      }
    }, 1000);
  }
}

new PPTController();
