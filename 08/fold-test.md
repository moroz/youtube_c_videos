---
title: "Secure cookie library in Go from scratch"
date: 2025-02-06
slug: "secure-cookie-library-in-go-from-scratch"
summary: In this post, I show you how to write a "secure cookie" library that will encrypt and authenticate payloads using the XChaCha20-Poly1305 AEAD, using the Go programming language.
lang: en
---

### Introduction: What are cookies and why should I care?

Cookies are short[^1] strings of letters, digits, and symbols[^2] that a Web server may store in your browser.
They are used to identify a user of a given Website between requests.
Whenever you add a product to a virtual shopping cart or sign in to an online mailbox, that Website is going to give you a _cookie_ that the server can later use to identify you.

