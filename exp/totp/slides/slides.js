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
      .then(() => this.setSlide(0));
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
}

new PPTController();
